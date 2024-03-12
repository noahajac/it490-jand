#!/usr/bin/env php
<?php
/**
 * Bootstraps JAND DMZ service.
 *
 * @package JAND\Dmz\Bootstrap
 */

namespace JAND\Dmz;

require_once __DIR__.'/common/Autoload.inc';
\JAND\Common\Autoload::register();
Includes\Service::start();
