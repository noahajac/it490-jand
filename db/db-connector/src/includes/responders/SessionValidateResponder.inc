<?php
/**
 * Contains the responder for a session validate request.
 *
 * @package JAND\DbConnector\Includes\Responders\SessionValidateResponder
 */

namespace JAND\DbConnector\Includes\Responders;

/**
 * Responds to session validate requests.
 */
abstract class SessionValidateResponder
{


    /**
     * Responds to a session validate request.
     *
     * @param \JAND\Common\Messages\Frontend\SessionValidateRequest $request Session validate request.
     * @param \PDO                                                  $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\SessionValidateResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Frontend\SessionValidateRequest $request, \PDO $pdo)
    {
        // Request is to validate.
        $sessionToken = $request->getSessionToken();

        // Example MySQL query to check if session exists and is not expired.
        $stmt = $pdo->prepare(
            "SELECT
UNIX_TIMESTAMP(CONVERT_TZ(sessions.expires_at, @@session.time_zone, 'UTC')) as expiration,
users.user_id as user_id,
users.first_name as first_name,
users.last_name as last_name
FROM sessions, users WHERE sessions.session_token = :sessionToken AND
sessions.user_id = users.user_id AND
sessions.expires_at > NOW()"
        );
        $stmt->execute(['sessionToken' => $sessionToken]);
        $session = $stmt->fetch();
        $stmt->closeCursor();

        // Check if the session exists and is not expired.
        if ($session) {
            // Session is valid and not expired.
            return new \JAND\Common\Messages\Frontend\SessionValidateResponse(
                true,
                new \JAND\Common\Session(
                    $sessionToken,
                    $session['expiration'],
                    $session['user_id'],
                    $session['first_name'],
                    $session['last_name']
                )
            );
        } else {
            // Session does not exist or is expired.
            return new \JAND\Common\Messages\Frontend\SessionValidateResponse(false);
        }

    }//end respondToRequest()


}//end class
