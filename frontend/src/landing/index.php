<?php
/**
 * Loads the landing page.
 *
 * @package JAND\Frontend\Landing\Index
 */

namespace JAND\Frontend\Landing;

require_once __DIR__.'/../common/Autoload.inc';
\JAND\Common\Autoload::register();

Includes\Landing::echoLanding();
