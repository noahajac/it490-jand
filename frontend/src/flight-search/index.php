<?php
/**
 * Loads the flight search page.
 *
 * @package JAND\Frontend\FlightSearch\Index
 */

namespace JAND\Frontend\FlightSearch;

require_once __DIR__.'/../common/Autoload.inc';
\JAND\Common\Autoload::register();

Includes\FlightSearch::processFlightSearch();
