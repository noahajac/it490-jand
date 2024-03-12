<?php
/**
 * Loads the user trips page.
 *
 * @package JAND\Frontend\Api\CheckAirport\Index
 */

namespace JAND\Frontend\Api\CheckAirport;

require_once __DIR__.'/../../common/Autoload.inc';
\JAND\Common\Autoload::register();

Includes\CheckAirport::processCheckAirport();
