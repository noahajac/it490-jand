<?php
/**
 * Loads the recommendations page.
 *
 * @package JAND\Frontend\Recommendations\Index
 */

namespace JAND\Frontend\Recommendations;

require_once __DIR__.'/../common/Autoload.inc';
\JAND\Common\Autoload::register();

Includes\Recommendations::echoRecommendations();
