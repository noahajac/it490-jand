<?php
/**
 * Contains the responder for a session invalidate request.
 *
 * @package JAND\DbConnector\Includes\Responders\SessionInvalidateResponder
 */

namespace JAND\DbConnector\Includes\Responders;

/**
 * Responds to session invalidate requests.
 */
abstract class SessionInvalidateResponder
{


    /**
     * Responds to a session invalidate request.
     *
     * @param \JAND\Common\Messages\Frontend\SessionInvalidateRequest $request Session invalidate request.
     * @param \PDO                                                    $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\SessionInvalidateResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Frontend\SessionInvalidateRequest $request, \PDO $pdo)
    {
        $sessionToken = $request->getSessionToken();

        // Example MySQL query to check if session exists.
        $stmt = $pdo->prepare('SELECT * FROM sessions WHERE session_token = :sessionToken');
        $stmt->execute(['sessionToken' => $sessionToken]);
        $session = $stmt->fetch();

        // Check if the session exists.
        if ($session) {
            // Mark the session as expired by setting the expiration timestamp to 0.
            $updateStmt = $pdo->prepare(
                "UPDATE sessions SET expires_at = '1970-01-01 00:00:00' WHERE session_token = :sessionToken"
            );
            $updateStmt->execute(['sessionToken' => $sessionToken]);

            // Return success.
            return new \JAND\Common\Messages\Frontend\SessionInvalidateResponse(true);
        } else {
            // Session does not exist.
            return new \JAND\Common\Messages\Frontend\SessionInvalidateResponse(false);
        }

    }//end respondToRequest()


}//end class
