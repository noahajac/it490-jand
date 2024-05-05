#!/usr/bin/env php
<?php
/**
 * Bootstraps JAND logger service.
 *
 * @package JAND\Logger\Bootstrap
 */

namespace JAND\Logger;

require_once __DIR__.'/common/Autoload.inc';
\JAND\Common\Autoload::register();
Includes\Logger::start();
