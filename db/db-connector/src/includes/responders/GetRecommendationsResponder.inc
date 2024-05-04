<?php
/**
 * Contains the responder for a get recommendations request.
 *
 * @package JAND\DbConnector\Includes\Responders\GetRecommendationsResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use JAND\Common\Messages\Shared\AirportCitySearchRequest;
use JAND\Common\Trips\Poi;

/**
 * Responds to get recommendation requests.
 */
abstract class GetRecommendationsResponder
{


    /**
     * Responds to get recommendation requests.
     *
     * @param \JAND\Common\Messages\Frontend\GetRecommendationsRequest $request Recommendations request.
     * @param \PDO                                                     $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\GetRecommendationsResponse Response to request.
     */
    public static function respondToRequest(
        \JAND\Common\Messages\Frontend\GetRecommendationsRequest $request,
        \PDO $pdo
    ) {
        $sessionToken = $request->getSessionToken();

        $stmt = $pdo->prepare(
            'SELECT p.*,r.rating,k.keyword FROM poi p 
LEFT JOIN poi_reviews r ON p.poi_id=r.poi_id LEFT JOIN 
(poi_keywords k INNER JOIN user_keyword_preferences u ON k.keyword=u.keyword) 
ON p.poi_id=k.poi_id INNER JOIN sessions s ON u.user_id=s.user_id 
AND s.session_token=:sessionToken WHERE p.poi_id NOT IN 
(SELECT poi_id FROM hide_poi WHERE user_id=u.user_id) 
GROUP BY p.poi_id ORDER BY -k.keyword DESC, -r.rating DESC LIMIT 5'
        );
        $stmt->execute(['sessionToken' => $sessionToken]);
        $results = $stmt->fetchAll();
        $stmt->closeCursor();

        $recommendations = [];

        foreach ($results as &$result) {
            $city = AirportCitySearchResponder::respondToRequest(
                new AirportCitySearchRequest(
                    $result['city'],
                ),
                $pdo
            )->getResults()[0];

            $tagsStmt = $pdo->prepare(
                'SELECT k.keyword FROM poi_keywords k, poi p WHERE p.poi_id=k.poi_id AND p.poi_id=:poiId'
            );
            $tagsStmt->execute(['poiId' => $result['poi_id']]);
            $tagsResults = $tagsStmt->fetchAll();
            $tagsStmt->closeCursor();

            $tags = [];

            foreach ($tagsResults as &$tag) {
                array_push($tags, $tag['keyword']);
            }

            array_push(
                $recommendations,
                new Poi(
                    $result['poi_id'],
                    $city,
                    $tags,
                    $result['poi_name']
                )
            );
        }//end foreach

        return new \JAND\Common\Messages\Frontend\GetRecommendationsResponse($recommendations);

    }//end respondToRequest()


}//end class
