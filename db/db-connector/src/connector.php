#!/usr/bin/env php
<?php

namespace JAND\DbConnector;

require_once(__DIR__ . '/common/autoload/autoload.inc.php');
\JAND\Common\Autoload\Autoload::register();

class Connector
{
  private \JAND\Common\RabbitMq\RabbitMqServer $server;
  private \PDO $pdo;

  function __construct()
  {
    $this->server = new \JAND\Common\RabbitMq\RabbitMqServer(__DIR__ . '/rabbitmq.ini', 'db-frontend_db.server');

    $dsn = 'mysql:host=localhost;dbname=Users_Sessions_Tables;charset=utf8';
    $username = 'testUser';
    $password = '12345';
    $this->pdo = new \PDO($dsn, $username, $password);
    $this->pdo->setAttribute(\PDO::ATTR_ERRMODE, \PDO::ERRMODE_EXCEPTION);
  }

  /**
   * Requests from the message broker get processed here.
   * 
   * @param mixed $request The request.
   * @return mixed Request response, false if unknown.
   */
  private function requestProcessor(mixed $request)
  {
    if ($request instanceof \JAND\Common\Messages\Frontend\LoginRequest) {




      // Request is to login.
      $email = $request->getEmail();
      $password = $request->getPassword();
      $stmt = $this->pdo->prepare("SELECT * FROM users WHERE email = :email");
      $stmt->execute(['email' => $email]);
      $user = $stmt->fetch();
      if ($user && password_verify($password, $user['password'])) {
        //generate session token
        $sessionToken = bin2hex(random_bytes(16)); // Generate a random token of 32 characters (16 bytes)
        $expirationTime = time() + 43200;
        $stmt = $this->pdo->prepare("INSERT INTO sessions (user_id, session_token, expires_at) VALUES (:userId, :sessionToken, CONVERT_TZ(FROM_UNIXTIME(:expiration), 'UTC', @@session.time_zone))");
        $stmt->execute(['userId' => $user['user_id'], 'sessionToken' => $sessionToken, 'expiration' => $expirationTime]); // Set expiration time to 12 hours from now
        return new \JAND\Common\Messages\Frontend\LoginResponse(
          true,
          new \JAND\Common\Utilities\Session($sessionToken, $expirationTime, $user['first_name'], $user['last_name'])
        );
      } else {
        return new \JAND\Common\Messages\Frontend\LoginResponse(false);
      }





    } else if ($request instanceof \JAND\Common\Messages\Frontend\RegisterRequest) {



      // Request is to register.
      $email = $request->getEmail();
      $password = $request->getPassword();
      $firstName = $request->getFirstName();
      $lastName = $request->getLastName();

      // Example MySQL query to insert user details into the users table
      $stmt = $this->pdo->prepare("INSERT INTO users (email, password, first_name, last_name) VALUES (:email, :password, :firstName, :lastName)");
      $stmt->execute(['email' => $email, 'password' => password_hash($password, PASSWORD_DEFAULT), 'firstName' => $firstName, 'lastName' => $lastName]);

      // Generate a session token
      $sessionToken = bin2hex(random_bytes(16)); // Generate a 32-character hexadecimal string
      $expirationTime = time() + 43200;

      // Example MySQL query to insert a new session for the user
      $stmt = $this->pdo->prepare("INSERT INTO sessions (user_id, session_token, expires_at) VALUES (:userId, :sessionToken, CONVERT_TZ(FROM_UNIXTIME(:expiration), 'UTC', @@session.time_zone))");
      $stmt->execute(['userId' => $this->pdo->lastInsertId(), 'sessionToken' => $sessionToken, 'expiration' => $expirationTime]);
      return new \JAND\Common\Messages\Frontend\RegisterResponse(
        true,
        new \JAND\Common\Utilities\Session($sessionToken, $expirationTime, $firstName, $lastName)
      );





    } else if ($request instanceof \JAND\Common\Messages\Frontend\SessionValidateRequest) {
      
      
      
      // Request is to validate

      $sessionToken = $request->getSessionToken();

      // Example MySQL query to check if session exists and is not expired
      $stmt = $this->pdo->prepare(
        "SELECT
UNIX_TIMESTAMP(CONVERT_TZ(sessions.expires_at, @@session.time_zone, 'UTC')) as expiration,
users.first_name as first_name,
users.last_name as last_name
FROM sessions, users WHERE sessions.session_token = :sessionToken AND
sessions.user_id = users.user_id AND
sessions.expires_at > NOW()"
      );
      $stmt->execute(['sessionToken' => $sessionToken]);
      $session = $stmt->fetch();


      // Check if the session exists and is not expired
      if ($session) {
        // Session is valid and not expired
        return new \JAND\Common\Messages\Frontend\SessionValidateResponse(true, new \JAND\Common\Utilities\Session(
          $sessionToken,
          $session['expiration'],
          $session['first_name'],
          $session['last_name']
        ));
      } else {
        // Session does not exist or is expired
        return new \JAND\Common\Messages\Frontend\SessionValidateResponse(false);
      }



    } else if ($request instanceof \JAND\Common\Messages\Frontend\SessionInvalidateRequest) {



      // Request is to invalidate.

      $sessionToken = $request->getSessionToken();

      // Example MySQL query to check if session exists
      $stmt = $this->pdo->prepare("SELECT * FROM sessions WHERE session_token = :sessionToken");
      $stmt->execute(['sessionToken' => $sessionToken]);
      $session = $stmt->fetch();

      // Check if the session exists
      if ($session) {
        // Mark the session as expired by setting the expiration timestamp to 0
        $updateStmt = $this->pdo->prepare("UPDATE sessions SET expires_at = '1970-01-01 00:00:00' WHERE session_token = :sessionToken");
        $updateStmt->execute(['sessionToken' => $sessionToken]);

        // Return success
        return new \JAND\Common\Messages\Frontend\SessionInvalidateResponse(true);
      } else {
        // Session does not exist
        return new \JAND\Common\Messages\Frontend\SessionInvalidateResponse(false);
      }
    } else {
      return false;
    }
  }

  function listen()
  {
    $this->server->process_requests(function (string $requestString) {
      return serialize(
        $this->requestProcessor(unserialize($requestString))
      );
    });
  }
}

(new Connector())->listen();
