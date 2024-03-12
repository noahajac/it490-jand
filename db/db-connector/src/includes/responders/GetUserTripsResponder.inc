<?php
/**
 * Contains the responder for a get user trips request.
 *
 * @package JAND\DbConnector\Includes\Responders\GetUserTripsResponder
 */

namespace JAND\DbConnector\Includes\Responders;

/**
 * Responds to get user trip requests.
 */
abstract class GetUserTripsResponder
{


    /**
     * Responds to a get user trips request.
     *
     * @param \JAND\Common\Messages\Frontend\GetUserTripsRequest $request User trips request.
     * @param \PDO                                               $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\GetUserTripsResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Frontend\GetUserTripsRequest $request, \PDO $pdo)
    {
        $sessionToken = $request->getSessionToken();

        $stmt = $pdo->prepare(
            'SELECT t.* ,c.* FROM 
user_trips as t, airport_cities as c, sessions as s WHERE t.iata_code=c.iata_code 
AND t.user_id=s.user_id AND s.session_token = :sessionToken'
        );
        $stmt->execute(['sessionToken' => $sessionToken]);
        $dbResults = $stmt->fetchAll();
        $stmt->closeCursor();

        $trips = [];

        foreach ($dbResults as &$result) {
            array_push(
                $trips,
                new \JAND\Common\Trips\UserTrip(
                    $result['trip_id'],
                    new \JAND\Common\Trips\AirportCity(
                        $result['iata_code'],
                        $result['name'],
                        $result['latitude'],
                        $result['longitude'],
                        $result['state_code'],
                        $result['country_code']
                    ),
                    new \DateTime($result['start_date']),
                    new \DateTime($result['end_date'])
                )
            );
        }

        return new \JAND\Common\Messages\Frontend\GetUserTripsResponse($trips);

    }//end respondToRequest()


}//end class
