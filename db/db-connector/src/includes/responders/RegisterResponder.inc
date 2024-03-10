<?php
/**
 * Contains the responder for a register request.
 *
 * @package JAND\DbConnector\Includes\Responders\RegisterResponder
 */

namespace JAND\DbConnector\Includes\Responders;

/**
 * Responds to register requests.
 */
abstract class RegisterResponder
{


    /**
     * Responds to a Register request.
     *
     * @param \JAND\Common\Messages\Frontend\RegisterRequest $request Register request.
     * @param \PDO                                           $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\RegisterResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Frontend\RegisterRequest $request, \PDO $pdo)
    {
        $email     = $request->getEmail();
        $password  = $request->getPassword();
        $firstName = $request->getFirstName();
        $lastName  = $request->getLastName();

        // Example MySQL query to insert user details into the users table.
        $stmt = $pdo->prepare(
            'INSERT INTO users (email, password, first_name, last_name) 
VALUES (:email, :password, :firstName, :lastName)'
        );
        $stmt->execute(
            [
                'email'     => $email,
                'password'  => password_hash($password, PASSWORD_DEFAULT),
                'firstName' => $firstName,
                'lastName'  => $lastName,
            ]
        );

        // Generate a session token.
        $sessionToken = bin2hex(random_bytes(16));
        // Generate a 32-character hexadecimal string.
        $expirationTime = (time() + 43200);

        // Example MySQL query to insert a new session for the user.
        $stmt = $pdo->prepare(
            "INSERT INTO sessions (user_id, session_token, expires_at) 
VALUES (:userId, :sessionToken, CONVERT_TZ(FROM_UNIXTIME(:expiration), 'UTC', @@session.time_zone))"
        );
        $stmt->execute(
            [
                'userId'       => $pdo->lastInsertId(),
                'sessionToken' => $sessionToken,
                'expiration'   => $expirationTime,
            ]
        );
        return new \JAND\Common\Messages\Frontend\RegisterResponse(
            true,
            new \JAND\Common\Session($sessionToken, $expirationTime, $firstName, $lastName)
        );

    }//end respondToRequest()


}//end class
