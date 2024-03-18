<?php
/**
 * Contains the responder for a get POI reviews request.
 *
 * @package JAND\DbConnector\Includes\Responders\GetPoiReviewsResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use JAND\Common\Messages\Shared\AirportCitySearchRequest;
use JAND\Common\Trips\Poi;
use JAND\Common\Trips\PoiReview;

/**
 * Responds to get POI review requests.
 */
abstract class GetPoiReviewsResponder
{


    /**
     * Responds to a get POI reviews request.
     *
     * @param \JAND\Common\Messages\Frontend\GetPoiReviewsRequest $request Get request.
     * @param \PDO                                                $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\GetReviewsResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Frontend\GetPoiReviewsRequest $request, \PDO $pdo)
    {
        $sessionToken = $request->getSessionToken();
        $poi          = $request->getPoi();

        $stmt = $pdo->prepare(
            'SELECT * FROM poi_reviews r, poi p WHERE r.poi_id=:poiId AND 
r.poi_id=p.poi_id'
        );
        $stmt->execute(
            [
                'poiId' => $poi->getPoiId(),
            ]
        );
        $dbResults = $stmt->fetchAll();
        $stmt->closeCursor();

        $reviews = [];

        foreach ($dbResults as &$result) {
            $city = AirportCitySearchResponder::respondToRequest(
                new AirportCitySearchRequest(
                    $result['city'],
                ),
                $pdo
            )->getResults()[0];
            array_push(
                $reviews,
                new PoiReview(
                    $result['review_id'],
                    $result['rating'],
                    $result['comment'],
                    new Poi(
                        $result['poi_id'],
                        $city,
                        [],
                        $result['poi_name']
                    )
                )
            );
        }//end foreach

        $stmt = $pdo->prepare(
            'SELECT r.*, p.* FROM poi_reviews r, poi p, sessions s WHERE r.poi_id=:poiId AND 
r.user_id=s.user_id AND s.session_token = :sessionToken AND p.poi_id=r.poi_id'
        );
        $stmt->execute(
            [
                'poiId'        => $poi->getPoiId(),
                'sessionToken' => $sessionToken,
            ]
        );
        $own = $stmt->fetch();
        if ($own === false) {
            $own = null;
        } else {
            $city = AirportCitySearchResponder::respondToRequest(
                new AirportCitySearchRequest(
                    $own['city'],
                ),
                $pdo
            )->getResults()[0];
            $own  = new PoiReview(
                $own['review_id'],
                $own['rating'],
                $own['comment'],
                new Poi(
                    $own['poi_id'],
                    $city,
                    [],
                    $own['poi_name']
                )
            );
        }//end if

        return new \JAND\Common\Messages\Frontend\GetReviewsResponse($reviews, $own);

    }//end respondToRequest()


}//end class
