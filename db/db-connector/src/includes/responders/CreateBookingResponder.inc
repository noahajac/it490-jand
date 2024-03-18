<?php
/**
 * Contains the responder for a create booking request.
 *
 * @package JAND\DbConnector\Includes\Responders\CreateBookingResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use JAND\Common\Trips\AirlineReview;
use JAND\Common\Trips\FlightItinerary;
use JAND\Common\Trips\HotelReview;

/**
 * Responds to create booking requests.
 */
abstract class CreateBookingResponder
{


    /**
     * Responds to a create booking request.
     *
     * @param \JAND\Common\Messages\Frontend\CreateBookingRequest $request Create request.
     * @param \PDO                                                $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\CreateBookingResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Frontend\CreateBookingRequest $request, \PDO $pdo)
    {
        $sessionToken = $request->getSessionToken();
        $booking      = $request->getBooking();

        if ($booking instanceof FlightItinerary) {
            $stmt = $pdo->prepare(
                'INSERT INTO flight_bookings VALUES 
    ((SELECT user_id FROM sessions WHERE session_token=:sessionToken), 
    :itineraryId, DEFAULT) 
ON DUPLICATE KEY UPDATE itinerary_id=:itineraryId'
            );
        } else {
            $stmt = $pdo->prepare(
                'INSERT INTO hotel_bookings VALUES 
    ((SELECT user_id FROM sessions WHERE session_token=:sessionToken), 
    :itineraryId, DEFAULT) 
ON DUPLICATE KEY UPDATE itinerary_id=:itineraryId'
            );
        }//end if

        $stmt->execute(
            [
                'sessionToken' => $sessionToken,
                'itineraryId'  => $booking->getItineraryId(),
            ]
        );
        $stmt->closeCursor();

        return new \JAND\Common\Messages\Frontend\CreateBookingResponse();

    }//end respondToRequest()


}//end class
