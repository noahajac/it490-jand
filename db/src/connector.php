#!/usr/bin/env php
<?php

require_once('includes/common/messages.inc.php');
require_once('includes/common/rabbitMQLib.inc.php');

$server = new rabbitMQServer('includes/rabbitmq.ini');

$server->process_requests(function (string $request_string) {
  return serialize(
    requestProcessor(unserialize($request_string))
  );
});

/**
 * Requests from the message broker get processed here.
 * 
 * @param mixed $request The request.
 * @return mixed Request response, false if unknown.
*/
function requestProcessor(mixed $request) {
  if ($request instanceof JAND\Frontend\LoginRequest) {
    // Request is to login.
    $email = $request->getEmail();
    $password_hash = $request->getPasswordHash();
    if ($email === 'test@test.com') {
      return new JAND\Frontend\LoginResponse(true, 'IamAsessionTOKEN', time()+60);
    } else {
      return new JAND\Frontend\LoginResponse(false, null, null);
    }
  } else if ($request instanceof JAND\Frontend\RegisterRequest) {
    $email = $request->getEmail();
    $password_hash = $request->getPasswordHash();
    $first_name = $request->getFirstName();
    $last_name = $request->getLastName(); 
  } else {
    return false;
  }
}
