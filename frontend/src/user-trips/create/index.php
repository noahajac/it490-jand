<?php
/**
 * Loads the user trip create/update page.
 *
 * @package JAND\Frontend\UserTrips\Create\Index
 */

namespace JAND\Frontend\UserTrips\Create;

require_once __DIR__.'/../../common/Autoload.inc';
\JAND\Common\Autoload::register();

Includes\CreateUserTrip::bootstrapCreateUserTrip();
