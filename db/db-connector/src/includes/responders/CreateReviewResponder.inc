<?php
/**
 * Contains the responder for a create or update review request.
 *
 * @package JAND\DbConnector\Includes\Responders\CreateReviewResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use JAND\Common\Trips\AirlineReview;
use JAND\Common\Trips\HotelReview;

/**
 * Responds to create or update review requests.
 */
abstract class CreateReviewResponder
{


    /**
     * Responds to a create or update user trip request.
     *
     * @param \JAND\Common\Messages\Frontend\CreateReviewRequest $request Create request.
     * @param \PDO                                               $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\CreateReviewResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Frontend\CreateReviewRequest $request, \PDO $pdo)
    {
        $sessionToken = $request->getSessionToken();
        $review       = $request->getReview();

        if ($review instanceof AirlineReview) {
            $stmt = $pdo->prepare(
                'INSERT INTO airline_reviews VALUES 
    (null, (SELECT user_id FROM sessions WHERE session_token=:sessionToken), 
    (SELECT iata_code FROM airlines WHERE iata_code=:iataCode), :rating, :comment, DEFAULT) 
ON DUPLICATE KEY UPDATE rating=:rating, comment=:comment'
            );

            $stmt->execute(
                [
                    'sessionToken' => $sessionToken,
                    'iataCode'     => $review->getAirline()->getCode(),
                    'rating'       => $review->getRating(),
                    'comment'      => $review->getComment(),
                ]
            );
            $stmt->closeCursor();
        } else if ($review instanceof HotelReview) {
            $stmt = $pdo->prepare(
                'INSERT INTO hotel_reviews VALUES 
    (null, (SELECT user_id FROM sessions WHERE session_token=:sessionToken), 
    (SELECT hotel_id FROM hotels WHERE hotel_id=:hotelId), :rating, :comment, DEFAULT) 
 ON DUPLICATE KEY UPDATE rating=:rating, comment=:comment'
            );

            $stmt->execute(
                [
                    'sessionToken' => $sessionToken,
                    'hotelId'      => $review->getHotel()->getHotelId(),
                    'rating'       => $review->getRating(),
                    'comment'      => $review->getComment(),
                ]
            );
            $stmt->closeCursor();
        } else {
            $stmt = $pdo->prepare(
                'INSERT INTO poi_reviews VALUES 
    (null, (SELECT user_id FROM sessions WHERE session_token=:sessionToken), 
    (SELECT poi_id FROM poi WHERE poi_id=:poiId), :rating, :comment, DEFAULT) 
 ON DUPLICATE KEY UPDATE rating=:rating, comment=:comment'
            );

            $stmt->execute(
                [
                    'sessionToken' => $sessionToken,
                    'poiId'        => $review->getPoi()->getPoiId(),
                    'rating'       => $review->getRating(),
                    'comment'      => $review->getComment(),
                ]
            );
            $stmt->closeCursor();
        }//end if

        return new \JAND\Common\Messages\Frontend\CreateUserTripResponse();

    }//end respondToRequest()


}//end class
