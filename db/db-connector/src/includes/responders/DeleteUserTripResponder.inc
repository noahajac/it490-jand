<?php
/**
 * Contains the responder for a delete user trip request.
 *
 * @package JAND\DbConnector\Includes\Responders\DeleteUserTripResponder
 */

namespace JAND\DbConnector\Includes\Responders;

/**
 * Responds to delete user trip requests.
 */
abstract class DeleteUserTripResponder
{


    /**
     * Responds to a delete user trip request.
     *
     * @param \JAND\Common\Messages\Frontend\DeleteUserTripRequest $request User trips request.
     * @param \PDO                                                 $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\DeleteUserTripResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Frontend\DeleteUserTripRequest $request, \PDO $pdo)
    {
        $sessionToken = $request->getSessionToken();

        $stmt = $pdo->prepare(
            'DELETE t FROM 
user_trips t, sessions s WHERE t.trip_id = :tripId 
AND t.user_id=s.user_id AND s.session_token = :sessionToken'
        );
        $stmt->execute(['sessionToken' => $sessionToken, 'tripId' => $request->getTripId()]);
        $stmt->closeCursor();

        return new \JAND\Common\Messages\Frontend\DeleteUserTripResponse();

    }//end respondToRequest()


}//end class
