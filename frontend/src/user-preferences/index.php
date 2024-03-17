<?php
/**
 * Loads the user preferences page.
 *
 * @package JAND\Frontend\UserPreferences\Index
 */

namespace JAND\Frontend\UserPreferences;

require_once __DIR__.'/../common/Autoload.inc';
\JAND\Common\Autoload::register();

Includes\UserPreferences::processUserPreferences();
