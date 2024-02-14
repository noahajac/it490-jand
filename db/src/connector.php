#!/usr/bin/env php
<?php

require_once('includes/common/messages.inc.php');
require_once('includes/common/rabbitMQLib.inc.php');

$server = new rabbitMQServer('includes/rabbitmq.ini');

$server->process_requests(function (string $request_string) {
  return serialize(
    request_processor(unserialize($request_string))
  );
});

/**
 * Requests from the message broker get processed here.
 * 
 * @param mixed $request The request.
 * @return mixed Request response, false if unknown.
*/
function request_processor(mixed $request) {
  if ($request instanceof JAND\Frontend\LoginRequest) {
    // Request is to login.
    $email = $request->get_email();
    $password_hash = $request->get_password_hash();
    return new JAND\Frontend\LoginResponse(true, 'IamAsessionTOKEN', time()+60);
  } else if ($request instanceof JAND\Frontend\RegisterRequest) {
    $email = $request->get_email();
    $password_hash = $request->get_password_hash();
    $first_name = $request->get_first_name();
    $last_name = $request->get_last_name(); 
  } else {
    return false;
  }
}
