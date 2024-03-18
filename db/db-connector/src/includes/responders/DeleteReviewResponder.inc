<?php
/**
 * Contains the responder for a delete review request.
 *
 * @package JAND\DbConnector\Includes\Responders\DeleteReviewResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use JAND\Common\Trips\AirlineReview;
use JAND\Common\Trips\HotelReview;

/**
 * Responds to delete review requests.
 */
abstract class DeleteReviewResponder
{


    /**
     * Responds to a delete review request.
     *
     * @param \JAND\Common\Messages\Frontend\DeleteReviewRequest $request Delete review request.
     * @param \PDO                                               $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\DeleteReviewResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Frontend\DeleteReviewRequest $request, \PDO $pdo)
    {
        $sessionToken = $request->getSessionToken();
        $review       = $request->getReview();

        if ($review instanceof AirlineReview) {
            $stmt = $pdo->prepare(
                'DELETE r FROM 
    airline_reviews r, sessions s WHERE r.iata_code = :iataCode 
    AND r.user_id=s.user_id AND s.session_token = :sessionToken'
            );
            $stmt->execute(
                [
                    'sessionToken' => $sessionToken,
                    'iataCode'     => $review->getAirline()->getCode(),
                ]
            );
        } else if ($review instanceof HotelReview) {
            $stmt = $pdo->prepare(
                'DELETE r FROM 
    hotel_reviews r, sessions s WHERE r.hotel_id = :hotelId 
    AND r.user_id=s.user_id AND s.session_token = :sessionToken'
            );
            $stmt->execute(
                [
                    'sessionToken' => $sessionToken,
                    'hotelId'      => $review->getHotel()->getHotelId(),
                ]
            );
        } else {
            $stmt = $pdo->prepare(
                'DELETE r FROM 
    poi_reviews r, sessions s WHERE r.poi_id = :poiId 
    AND r.user_id=s.user_id AND s.session_token = :sessionToken'
            );
            $stmt->execute(
                [
                    'sessionToken' => $sessionToken,
                    'poiId'        => $review->getPoi()->getPoiId(),
                ]
            );
        }//end if

        $stmt->closeCursor();

        return new \JAND\Common\Messages\Frontend\DeleteReviewResponse();

    }//end respondToRequest()


}//end class
