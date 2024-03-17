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

Includes\HotelSearch::processHotelSearch();
