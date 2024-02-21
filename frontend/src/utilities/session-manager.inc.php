<?php

/** Contains the frontend session manager. */

namespace JAND\Frontend\Utilities;

/**
 * This class will handle forming, sending, receiving,
 * and parsing any messages that have to do with sessions.
 */
abstract class SessionManager
{
  /** The session object that has been previously fetched. */
  private static \JAND\Common\Utilities\Session $session;

  /**
   * Gets the session object.
   * If frontend does not currently have one, fetch it through rabbit.
   * If the user does not have a session cookie set, will automatically
   * return false.
   * @return false|\JAND\Common\Utilities\Session Session object or false.
   */
  static function getSession()
  {
    if (!isset(static::$session)) {
      $cookieName = \JAND\Common\Config\Config::getConfig()->getSessionCookieName();
      $cookieValue = $_COOKIE[$cookieName] ?? null;

      if ($cookieValue === null) {
        return false;
      }

      $client = new \JAND\Common\RabbitMq\RabbitMqClient(__DIR__ . '/../rabbitmq.ini', 'db-frontend_frontend.client');
      $request = new \JAND\Common\Messages\Frontend\SessionValidateRequest($cookieValue);
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
    }
  }

  /**
   * Logs in through rabbit messaging. Will get session
   * and set user session cookie.
   * @param string $email User's email.
   * @param string $passwordHash User's password hash.
   * @return false|\JAND\Common\Utilities\Session Session object or false.
   */
  static function login(string $email, string $passwordHash)
  {
    $cookieName = \JAND\Common\Config\Config::getConfig()->getSessionCookieName();

    $client = new \JAND\Common\RabbitMq\RabbitMqClient(__DIR__ . '/../rabbitmq.ini', 'db-frontend_frontend.client');
    $request = new \JAND\Common\Messages\Frontend\LoginRequest($email, $passwordHash);
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
            !(\JAND\Common\Config\Config::getConfig()->getDevMode()), // Only make secure if dev mode is disabled.
          );
          static::$session = $session;
          return $session;
        }
      }
    }

    return false;
  }

  /**
   * Registers through rabbit messaging. Will get session
   * and set user session cookie.
   * @param string $email User's email.
   * @param string $passwordHash User's password hash.
   * @param string $firstName User's first name.
   * @param string $lastName User's last name.
   * @return false|\JAND\Common\Utilities\Session|\JAND\Common\Messages\Frontend\RegisterError Session object, error, or false.
   */
  static function register(string $email, string $passwordHash, string $firstName, string $lastName)
  {
    $cookieName = \JAND\Common\Config\Config::getConfig()->getSessionCookieName();

    $client = new \JAND\Common\RabbitMq\RabbitMqClient(__DIR__ . '/../rabbitmq.ini', 'db-frontend_frontend.client');
    $request = new \JAND\Common\Messages\Frontend\RegisterRequest($email, $passwordHash, $firstName, $lastName);
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
            !(\JAND\Common\Config\Config::getConfig()->getDevMode()), // Only make secure if dev mode is disabled.
          );
          static::$session = $session;
          return $session;
        }
      } else {
        $error = $response->getError();
        if ($error instanceof \JAND\Common\Messages\Frontend\RegisterError) {
          return $error;
        }
      }
    }

    return false;
  }

  /**
   * Logs out user session.
   * @return bool True on success, false on error.
   */
  static function logout()
  {
    $session = static::getSession();

    if (!$session) {
      return true;
    }

    $cookieName = \JAND\Common\Config\Config::getConfig()->getSessionCookieName();

    $client = new \JAND\Common\RabbitMq\RabbitMqClient(__DIR__ . '/../rabbitmq.ini', 'db-frontend_frontend.client');
    $request = new \JAND\Common\Messages\Frontend\SessionInvalidateRequest($session->getSessionToken());
    $response = $request->sendRequest($client);
    if ($response instanceof \JAND\Common\Messages\Frontend\SessionInvalidateResponse) {
      if ($response->getResult()) {
        $result = $response->getResult();
        if ($result) {
          setcookie(
            $cookieName,
            '',
            -1,
          );
          static::$session = null;
          return $result;
        }
      }
    }

    // This indicates some sort of error logging out.
    // This shouldn't ever happen.
    return false;
  }
}
