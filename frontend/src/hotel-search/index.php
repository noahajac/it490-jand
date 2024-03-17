<?php
/**
 * Loads the hotel search page.
 *
 * @package JAND\Frontend\HotelSearch\Index
 */

namespace JAND\Frontend\HotelSearch;

use JAND\Common\Trips\AirportCity;

require_once __DIR__.'/../common/Autoload.inc';
\JAND\Common\Autoload::register();

$request = new \JAND\Common\Messages\Shared\HotelItinerarySearchRequest(
    new AirportCity('EWR', 'Test', 0, 0, null, null),
    new \DateTime('2024-03-20'),
    new \DateTime('2024-03-21'),
    1
);

Includes\HotelSearch::processHotelSearch();
