<?php
/**
 * Loads the bookings page.
 *
 * @package JAND\Frontend\Bookings\Index
 */

namespace JAND\Frontend\Bookings;

require_once __DIR__.'/../common/Autoload.inc';
\JAND\Common\Autoload::register();

Includes\Bookings::echoBookings();
