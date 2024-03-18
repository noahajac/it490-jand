<?php
/**
 * Loads the booking create page.
 *
 * @package JAND\Frontend\Bookings\Create\Index
 */

namespace JAND\Frontend\Bookings\Create;

require_once __DIR__.'/../../common/Autoload.inc';
\JAND\Common\Autoload::register();

Includes\CreateBooking::bootstrapCreateUserTrip();
