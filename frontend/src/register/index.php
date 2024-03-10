<?php
/**
 * Loads the register page.
 *
 * @package JAND\Frontend\Register\Index
 */

namespace JAND\Frontend\Register;

require_once __DIR__.'/../common/Autoload.inc';
\JAND\Common\Autoload::register();

Includes\Register::echoRegister();
