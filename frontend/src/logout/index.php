<?php
/**
 * Loads the logout page.
 *
 * @package JAND\Frontend\Logout\Index
 */

namespace JAND\Frontend\Logout;

require_once __DIR__.'/../common/Autoload.inc';
\JAND\Common\Autoload::register();

Includes\Logout::echoLogout();
