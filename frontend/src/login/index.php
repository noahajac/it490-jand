<?php
/**
 * Loads the login page.
 *
 * @package JAND\Frontend\Login\Index
 */

namespace JAND\Frontend\Login;

require_once __DIR__.'/../common/Autoload.inc';
\JAND\Common\Autoload::register();

Includes\Login::echoLogin();
