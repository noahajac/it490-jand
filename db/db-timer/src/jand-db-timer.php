#!/usr/bin/env php
<?php
/**
 * Bootstraps JAND database timer.
 *
 * @package JAND\DbTimer\Bootstrap
 */

namespace JAND\DbTimer;

require_once __DIR__.'/common/Autoload.inc';
\JAND\Common\Autoload::register();
Includes\Timer::start();
