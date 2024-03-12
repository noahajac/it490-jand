<?php
/**
 * Contains the responder for a create or update user trip request.
 *
 * @package JAND\DbConnector\Includes\Responders\CreateUserTripResponder
 */

namespace JAND\DbConnector\Includes\Responders;

/**
 * Responds to create or update user trip requests.
 */
abstract class CreateUserTripResponder
{


    /**
     * Responds to a create or update user trip request.
     *
     * @param \JAND\Common\Messages\Frontend\CreateUserTripRequest $request User trips request.
     * @param \PDO                                                 $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\CreateUserTripResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Frontend\CreateUserTripRequest $request, \PDO $pdo)
    {
        $sessionToken = $request->getSessionToken();
        $trip         = $request->getUserTrip();
        $tripToUpdate = $trip->getTripId();

        if (empty($tripToUpdate)) {
            // New trip.
            $stmt = $pdo->prepare(
                'INSERT INTO user_trips VALUES 
(null, (SELECT user_id FROM sessions WHERE session_token=:sessionToken), 
(SELECT iata_code FROM airport_cities WHERE iata_code=:iataCode), :startDate, :endDate)'
            );

            $stmt->execute(
                [
                    'sessionToken' => $sessionToken,
                    'iataCode'     => $trip->getTripDestination()->getCode(),
                    'startDate'    => $trip->getTripStart()->format('Y-m-d'),
                    'endDate'      => $trip->getTripEnd()->format('Y-m-d'),
                ]
            );
            $stmt->closeCursor();
        } else {
            // Update existing trip.
            $stmt = $pdo->prepare(
                'UPDATE user_trips t, sessions s
SET t.iata_code = (SELECT iata_code FROM airport_cities WHERE iata_code=:iataCode), 
t.start_date = :startDate, t.end_date = :endDate WHERE t.trip_id=:tripId 
AND t.user_id = s.user_id AND s.session_token = :sessionToken'
            );
            $stmt->execute(
                [
                    'sessionToken' => $sessionToken,
                    'iataCode'     => $trip->getTripDestination()->getCode(),
                    'startDate'    => $trip->getTripStart()->format('Y-m-d'),
                    'endDate'      => $trip->getTripEnd()->format('Y-m-d'),
                    'tripId'       => $tripToUpdate,
                ]
            );
            $stmt->closeCursor();
        }//end if

        return new \JAND\Common\Messages\Frontend\CreateUserTripResponse();

    }//end respondToRequest()


}//end class
