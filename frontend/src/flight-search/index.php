<?php

namespace JAND\Frontend;

require_once __DIR__.'/../common/Autoload.inc';
\JAND\Common\Autoload::register();

$request  = new \JAND\Common\Messages\Shared\FlightItinerarySearchRequest(
    new \JAND\Common\Trips\AirportCity('EWR', 'Newark', 0, 0, '', ''),
    new \JAND\Common\Trips\AirportCity('MIA', 'MIA', 0, 0, '', ''),
    new \DateTime('2024-05-01'),
    new \DateTime('2024-05-04'),
    1
);
$response = $request->sendRequest(\JAND\Frontend\Includes\RabbitClientManager::getClient());
echo print_r($response);
