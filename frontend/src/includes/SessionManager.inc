<?php
/**
 * Contains the frontend session manager.
 *
 * @package JAND\Frontend\Includes\SessionManager
 */

namespace JAND\Frontend\Includes;

/**
 * This class will handle forming, sending, receiving,
 * and parsing any messages that have to do with sessions.
 */
abstract class SessionManager
{

    /**
     * The session object that has been previously fetched.
     *
     * @var ?\JAND\Common\Session $session User session object.
     */
    private static ?\JAND\Common\Session $session;


    /**
     * Gets the session object.
     * If frontend does not currently have one, fetch it through rabbit.
     * If the user does not have a session cookie set, will automatically
     * return false.
     *
     * @return false|\JAND\Common\Session Session object or false.
     */
    public static function getSession()
    {
        if (!isset(static::$session)) {
            $cookieName  = 'SESSION';
            $cookieValue = ($_COOKIE[$cookieName] ?? null);

            if ($cookieValue === null) {
                return false;
            }

            $client   = new \JAND\Common\RabbitMq\RabbitMqClient(
                __DIR__.'/rabbitmq.ini',
                'db-frontend_frontend.client'
            );
            $request  = new \JAND\Common\Messages\Frontend\SessionValidateRequest($cookieValue);
            $response = $request->sendRequest($client);
            if ($response instanceof \JAND\Common\Messages\Frontend\SessionValidateResponse) {
                if ($response->getResult()) {
                    $session = $response->getSession();
                    if ($session !== null) {
                        static::$session = $session;
                        return $session;
                    }
                }
            }

            return false;
        } else {
            return static::$session;
        }//end if

    }//end getSession()


    /**
     * Logs in through rabbit messaging. Will get session
     * and set user session cookie.
     *
     * @param string $email        User's email.
     * @param string $passwordHash User's password hash.
     *
     * @return false|\JAND\Common\Session Session object or false.
     */
    public static function login(string $email, string $passwordHash)
    {
        $cookieName = 'SESSION';

        $client   = new \JAND\Common\RabbitMq\RabbitMqClient(__DIR__.'/rabbitmq.ini', 'db-frontend_frontend.client');
        $request  = new \JAND\Common\Messages\Frontend\LoginRequest($email, $passwordHash);
        $response = $request->sendRequest($client);
        if ($response instanceof \JAND\Common\Messages\Frontend\LoginResponse) {
            if ($response->getResult()) {
                $session = $response->getSession();
                if ($session !== null) {
                    setcookie(
                        $cookieName,
                        $session->getSessionToken(),
                        $session->getSessionExpiration(),
                        '/',
                        $_SERVER['SERVER_NAME'],
                        !(getenv('JAND_DEV_MODE') === 'true'),
                        // Only make secure if dev mode is disabled.
                    );
                    static::$session = $session;
                    return $session;
                }
            }
        }

        return false;

    }//end login()


    /**
     * Registers through rabbit messaging. Will get session
     * and set user session cookie.
     *
     * @param string $email        User's email.
     * @param string $passwordHash User's password hash.
     * @param string $firstName    User's first name.
     * @param string $lastName     User's last name.
     *
     * @return false|\JAND\Common\Session|
     * \JAND\Common\Messages\Frontend\RegisterError Session object, error, or false.
     */
    public static function register(string $email, string $passwordHash, string $firstName, string $lastName)
    {
        $cookieName = 'SESSION';

        $client   = new \JAND\Common\RabbitMq\RabbitMqClient(__DIR__.'/rabbitmq.ini', 'db-frontend_frontend.client');
        $request  = new \JAND\Common\Messages\Frontend\RegisterRequest($email, $passwordHash, $firstName, $lastName);
        $response = $request->sendRequest($client);
        if ($response instanceof \JAND\Common\Messages\Frontend\RegisterResponse) {
            if ($response->getResult()) {
                $session = $response->getSession();
                if ($session !== null) {
                    setcookie(
                        $cookieName,
                        $session->getSessionToken(),
                        $session->getSessionExpiration(),
                        '/',
                        $_SERVER['SERVER_NAME'],
                        !(getenv('JAND_DEV_MODE') === 'true'),
                        // Only make secure if dev mode is disabled.
                    );
                    static::$session = $session;
                    return $session;
                }
            } else {
                $error = $response->getError();
                if ($error instanceof \JAND\Common\Messages\Frontend\RegisterError) {
                    return $error;
                }
            }//end if
        }//end if

        return false;

    }//end register()


    /**
     * Logs out user session.
     *
     * @return boolean True on success, false on error.
     */
    public static function logout()
    {
        $session = static::getSession();

        if (!$session) {
            return true;
        }

        $cookieName = 'SESSION';

        $client   = new \JAND\Common\RabbitMq\RabbitMqClient(__DIR__.'/rabbitmq.ini', 'db-frontend_frontend.client');
        $request  = new \JAND\Common\Messages\Frontend\SessionInvalidateRequest($session->getSessionToken());
        $response = $request->sendRequest($client);
        if ($response instanceof \JAND\Common\Messages\Frontend\SessionInvalidateResponse) {
            if ($response->getResult()) {
                $result = $response->getResult();
                if ($result) {
                    setcookie(
                        $cookieName,
                        '',
                        -1,
                        '/',
                        $_SERVER['SERVER_NAME'],
                        !(getenv('JAND_DEV_MODE') === 'true'),
                        // Only make secure if dev mode is disabled.
                    );
                      static::$session = null;
                      return $result;
                }
            }
        }

        // This indicates some sort of error logging out.
        // This shouldn't ever happen.
        return false;

    }//end logout()


}//end class
