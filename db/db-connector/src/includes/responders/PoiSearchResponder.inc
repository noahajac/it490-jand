<?php
/**
 * Contains the responder for a POI search request.
 *
 * @package JAND\DbConnector\Includes\Responders\PoiSearchResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use JAND\Common\Messages\Shared\AirportCitySearchRequest;
use JAND\Common\Trips\Hotel;
use JAND\Common\Trips\Poi;


/**
 * Responds to POI search requests.
 */
abstract class PoiSearchResponder
{


    /**
     * Responds to a POI search request.
     *
     * @param \JAND\Common\Messages\Shared\PoiSearchRequest $request POI search request.
     * @param \PDO                                          $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Shared\PoiSearchResponse Response to request.
     */
    public static function respondToRequest(
        \JAND\Common\Messages\Shared\PoiSearchRequest $request,
        \PDO $pdo
    ) {
        /*
         * Check db for an existing version of this query within a time frame.
         * If it exists, run a SELECT to craft the response.
         *
         * If not, send to DMZ. Once results received, add to DB, and reply.
         */

        $pastQueryCheck = $pdo->prepare(
            'SELECT COUNT(*) FROM poi_queries 
WHERE city = :city 
AND NOW() < pulled_on + INTERVAL 1 DAY'
        );

        $pastQueryCheck->execute(
            [
                'city' => $request->getCity()->getCode(),
            ]
        );

        $pastQueryResult = $pastQueryCheck->fetch();
        $pastQueryCheck->closeCursor();

        $pois = [];

        if ($pastQueryResult[0] < 1) {
            // Query was not made recently, pull from DMZ.
            $dmzRequest = new \JAND\Common\Messages\Shared\PoiSearchRequest(
                $request->getCity(),
            );

            /**
             * Response from DMZ.
             *
             * @var \JAND\Common\Messages\Shared\PoiSearchResponse $dmzResult
             */
            $dmzResult = $dmzRequest->sendRequest(\JAND\DbConnector\Includes\RabbitClientManager::getClient());

            foreach ($dmzResult->getPois() as &$poi) {
                $addPoiStmt = $pdo->prepare(
                    'INSERT INTO poi VALUES 
(null, :poiName, :city, DEFAULT) 
ON DUPLICATE KEY UPDATE poi_name=:poiName, city=:city, poi_id=LAST_INSERT_ID(poi_id)'
                );
                $addPoiStmt->execute(
                    [
                        'poiName' => $poi->getName(),
                        'city'    => $poi->getCity()->getCode(),
                    ]
                );
                $addPoiStmt->closeCursor();
                $poiId = $pdo->lastInsertId();

                foreach ($poi->getTags() as &$tag) {
                    $addPoiKeywordStmt = $pdo->prepare(
                        'INSERT INTO poi_keywords VALUES 
    (:poiId, :keyword) 
    ON DUPLICATE KEY UPDATE poi_id=:poiId, keyword=:keyword'
                    );
                    $addPoiKeywordStmt->execute(
                        [
                            'poiId'   => $poiId,
                            'keyword' => $tag,
                        ]
                    );
                    $addPoiKeywordStmt->closeCursor();
                }

                array_push(
                    $pois,
                    new \JAND\Common\Trips\Poi(
                        $poiId,
                        $request->getCity(),
                        $poi->getTags(),
                        $poi->getName()
                    )
                );
            }//end foreach

            // Add to poi queries log.
            $poiQueriesInsertStmt = $pdo->prepare(
                'INSERT INTO poi_queries VALUES 
(:city, DEFAULT)  
ON DUPLICATE KEY UPDATE city=:city'
            );

            $poiQueriesInsertStmt->execute(
                [
                    'city' => $request->getCity()->getCode(),
                ]
            );
            $poiQueriesInsertStmt->closeCursor();
        } else {
            // Query was made recently, pull from DB.
            $poiSelectStmt = $pdo->prepare(
                'SELECT * FROM poi WHERE city=:city'
            );
            $poiSelectStmt->execute(
                [
                    'city' => $request->getCity()->getCode(),
                ]
            );
            $poiSelectResults = $poiSelectStmt->fetchAll();
            $poiSelectStmt->closeCursor();

            foreach ($poiSelectResults as &$poi) {
                $city = AirportCitySearchResponder::respondToRequest(
                    new AirportCitySearchRequest(
                        $poi['city'],
                    ),
                    $pdo
                )->getResults()[0];

                $tags = [];

                $poiTagsSelectStmt = $pdo->prepare('SELECT * FROM poi_keywords WHERE poi_id=:poiId');
                $poiTagsSelectStmt->execute(
                    [
                        'poiId' => $poi['poi_id'],
                    ]
                );
                $poiTagsSelectResult = $poiTagsSelectStmt->fetchAll();
                $poiTagsSelectStmt->closeCursor();

                foreach ($poiTagsSelectResult as &$tag) {
                    array_push($tags, $tag['keyword']);
                }

                array_push(
                    $pois,
                    new \JAND\Common\Trips\Poi(
                        $poi['poi_id'],
                        $city,
                        $tags,
                        $poi['poi_name']
                    )
                );
            }//end foreach
        }//end if

        return new \JAND\Common\Messages\Shared\PoiSearchResponse($pois);

    }//end respondToRequest()


}//end class
