<?php
/**
 * Contains the responder for a get hotel reviews request.
 *
 * @package JAND\DbConnector\Includes\Responders\GetHotelReviewsResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use JAND\Common\Messages\Shared\AirportCitySearchRequest;
use JAND\Common\Trips\Hotel;
use JAND\Common\Trips\HotelReview;

/**
 * Responds to get hotel review requests.
 */
abstract class GetHotelReviewsResponder
{


    /**
     * Responds to a get hotel reviews request.
     *
     * @param \JAND\Common\Messages\Frontend\GetHotelReviewsRequest $request Get request.
     * @param \PDO                                                  $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\GetReviewsResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Frontend\GetHotelReviewsRequest $request, \PDO $pdo)
    {
        $sessionToken = $request->getSessionToken();
        $hotel        = $request->getHotel();

        $stmt = $pdo->prepare(
            'SELECT * FROM hotel_reviews r, hotels h WHERE r.hotel_id=:hotelId AND 
r.hotel_id=h.hotel_id'
        );
        $stmt->execute(
            [
                'hotelId' => $hotel->getHotelId(),
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
                new HotelReview(
                    $result['review_id'],
                    $result['rating'],
                    $result['comment'],
                    new Hotel(
                        $result['hotel_id'],
                        $city,
                        $result['hotel_code'],
                        $result['hotel_name']
                    )
                )
            );
        }//end foreach

        $stmt = $pdo->prepare(
            'SELECT r.*, h.* FROM hotel_reviews r, hotels h, sessions s WHERE r.hotel_id=:hotelId AND 
r.user_id=s.user_id AND s.session_token = :sessionToken AND h.hotel_id=r.hotel_id'
        );
        $stmt->execute(
            [
                'hotelId'      => $hotel->getHotelId(),
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
            $own  = new HotelReview(
                $own['review_id'],
                $own['rating'],
                $own['comment'],
                new Hotel(
                    $own['hotel_id'],
                    $city,
                    $own['hotel_code'],
                    $own['hotel_name']
                )
            );
        }//end if

        return new \JAND\Common\Messages\Frontend\GetReviewsResponse($reviews, $own);

    }//end respondToRequest()


}//end class
