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
      $password_hash = $request->getPasswordHash();
      if ($email === 'test@test.com') {
        return new \JAND\Common\Messages\Frontend\LoginResponse(true, 'IamAsessionTOKEN', time() + 60);
      } else {
        return new \JAND\Common\Messages\Frontend\LoginResponse(false, null, null);
      }
    } else if ($request instanceof \JAND\Common\Messages\Frontend\RegisterRequest) {
      $email = $request->getEmail();
      $password_hash = $request->getPasswordHash();
      $first_name = $request->getFirstName();
      $last_name = $request->getLastName();
    } else {
      return false;
    }
  }

  function listen() {
    $this->server->process_requests(function (string $request_string) {
      return serialize(
        static::requestProcessor(unserialize($request_string))
      );
    });
  }
}

(new Connector())->listen();