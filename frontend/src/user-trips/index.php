<?php
/**
 * Loads the user trips page.
 *
 * @package JAND\Frontend\UserTrips\Index
 */

namespace JAND\Frontend\UserTrips;

require_once __DIR__.'/../common/Autoload.inc';
\JAND\Common\Autoload::register();

Includes\UserTrips::echoUserTrips();
