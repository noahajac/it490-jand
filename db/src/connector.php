#!/usr/bin/env php
<?php

require_once('includes/common/messages.inc.php');
require_once('includes/common/rabbitMQLib.inc.php');

$server = new rabbitMQServer('includes/rabbitmq.ini');

function processRequest($request) {
  echo $request;
}

$server->process_requests('processRequest');
