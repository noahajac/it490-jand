<?php
/**
 * Contains the responder for a login request.
 *
 * @package JAND\DbConnector\Includes\Responders\LoginResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use JAND\DbConnector\Includes\LogSender;

/**
 * Responds to login requests.
 */
abstract class LoginResponder
{


    /**
     * Responds to a login request.
     *
     * @param \JAND\Common\Messages\Frontend\LoginRequest $request Login request.
     * @param \PDO                                        $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\LoginResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Frontend\LoginRequest $request, \PDO $pdo)
    {
        $email        = $request->getEmail();
            $password = $request->getPassword();
            $stmt     = $pdo->prepare('SELECT * FROM users WHERE email = :email');
            $stmt->execute(['email' => $email]);
            $user = $stmt->fetch();
            $stmt->closeCursor();
        if ($user && password_verify($password, $user['password'])) {
            // Generate session token.
            $sessionToken = bin2hex(random_bytes(16));
            // Generate a random token of 32 characters (16 bytes).
            $expirationTime = (time() + 43200);
            LogSender::sendLog('New login for user: '.$email);
            $stmt = $pdo->prepare(
                "INSERT INTO sessions (user_id, session_token, expires_at) VALUES 
(:userId, :sessionToken, CONVERT_TZ(FROM_UNIXTIME(:expiration), 'UTC', @@session.time_zone))"
            );
            $stmt->execute(
                [
                    'userId'       => $user['user_id'],
                    'sessionToken' => $sessionToken,
                    'expiration'   => $expirationTime,
                ]
            );
            $stmt->closeCursor();
            // Set expiration time to 12 hours from now.
            return new \JAND\Common\Messages\Frontend\LoginResponse(
                true,
                new \JAND\Common\Session(
                    $sessionToken,
                    $expirationTime,
                    $user['user_id'],
                    $user['first_name'],
                    $user['last_name']
                )
            );
        } else {
            return new \JAND\Common\Messages\Frontend\LoginResponse(false);
        }//end if

    }//end respondToRequest()


}//end class
