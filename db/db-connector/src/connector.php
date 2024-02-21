#!/usr/bin/env php
<?php

namespace JAND\DbConnector;

require_once(__DIR__ . '/common/autoload/autoload.inc.php');
\JAND\Common\Autoload\Autoload::register();

class Connector
{
  private \JAND\Common\RabbitMq\RabbitMqServer $server;

  function __construct()
  {
    $this->server = new \JAND\Common\RabbitMq\RabbitMqServer(__DIR__ . '/rabbitmq.ini');

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
  private static function requestProcessor(mixed $request)
  {
    if ($request instanceof \JAND\Common\Messages\Frontend\LoginRequest) {
      // Request is to login.
      $email = $request->getEmail();
      $passwordHash = $request->getPasswordHash();
      //mysql query
      $stmt = $this->pdo->prepare("SELECT * FROM users WHERE email = :email AND password_hash = :passwordHash");
      $stmt->execute(['email' => $email, 'passwordHash' => $passwordHash]);
      $user = $stmt->fetch();
      if ($user) {
        //generate session token
        $sessionToken = bin2hex(random_bytes(16)); // Generate a random token of 32 characters (16 bytes)
        // Insert session into SQL table
        $stmt = $this->pdo->prepare("INSERT INTO sessions (user_id, session_token, expires_at) VALUES (:userId, :sessionToken, :expiresAt)");
        $stmt->execute(['userId' => $user['id'], 'sessionToken' => $sessionToken, 'expiresAt' => time() + 60]); // Set expiration time to 60 seconds from now
        return new \JAND\Common\Messages\Frontend\LoginResponse(true, new\JAND\Common\Utilities\Session($sessionToken, time() + 60, $firstName, $lastName);
      } else {
        return new \JAND\Common\Messages\Frontend\LoginResponse(false, null, null);
      }
    } else if ($request instanceof \JAND\Common\Messages\Frontend\RegisterRequest) {
      $email = $request->getEmail();
      $passwordHash = $request->getPasswordHash();
      $firstName = $request->getFirstName();
      $lastName = $request->getLastName();
      // Extract username from email
      $emailParts = explode('@', $email);
      $username = $emailParts[0]; // Use the characters before '@' as the username

      // Example MySQL query to insert user details into the users table
      $stmt = $this->pdo->prepare("INSERT INTO users (username, password, email) VALUES (:username, :password, :email)");
      $stmt->execute(['username' => $username, 'password' => $passwordHash, 'email' => $email]);

      // Generate a session token
      $sessionToken = bin2hex(random_bytes(16)); // Generate a 32-character hexadecimal string

      // Example MySQL query to insert a new session for the user
      $stmt = $this->pdo->prepare("INSERT INTO sessions (user_id, session_token, expires_at) VALUES (:userId, :sessionToken, NOW())");
      $stmt->execute(['userId' => $this->pdo->lastInsertId(), 'sessionToken' => $sessionToken]);
      return new \JAND\Common\Messages\Frontend\RegisterResponse(true, $sessionToken);

    } else if ($request instanceof \JAND\Common\Messages\Frontend\SessionValidateRequest) {
      $sessionToken = $request->getSessionToken();

      // Example MySQL query to check if session exists and is not expired
      $stmt = $this->pdo->prepare("SELECT * FROM sessions WHERE session_token = :sessionToken AND NOW() < DATE_ADD(created_at, INTERVAL 1 HOUR)");
      $stmt->execute(['sessionToken' => $sessionToken]);
      $session = $stmt->fetch();
  
      // Check if the session exists and is not expired
      if ($session) {
          // Session is valid and not expired
          return new \JAND\Common\Messages\Frontend\SessionValidateResponse(true);
      } else {
          // Session does not exist or is expired
          return new \JAND\Common\Messages\Frontend\SessionValidateResponse(false);
      }
    }
      else if($request instanceof \JAND\Common\Messages\Frontend\SessionInvalidateRequest){
        $sessionToken = $request->getSessionToken();

    // Example MySQL query to check if session exists
    $stmt = $this->pdo->prepare("SELECT * FROM sessions WHERE session_token = :sessionToken");
    $stmt->execute(['sessionToken' => $sessionToken]);
    $session = $stmt->fetch();

    // Check if the session exists
    if ($session) {
        // Mark the session as expired by setting the expiration timestamp to 0
        $updateStmt = $this->pdo->prepare("UPDATE sessions SET expiration_timestamp = 0 WHERE session_token = :sessionToken");
        $updateStmt->execute(['sessionToken' => $sessionToken]);

        // Return success
        return new \JAND\Common\Messages\Frontend\SessionInvalidateResponse(true);
    } else {
        // Session does not exist
        return new \JAND\Common\Messages\Frontend\SessionInvalidateResponse(false);
    }
      }
      else {
      return false;
    }
  }

  function listen() {
    $this->server->process_requests(function (string $requestString) {
      return serialize(
        static::requestProcessor(unserialize($requestString))
      );
    });
  }
}

(new Connector())->listen();