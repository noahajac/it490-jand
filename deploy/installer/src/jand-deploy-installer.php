#!/usr/bin/env php
<?php
/**
 * Bootstraps JAND deploy installer daemon.
 *
 * @package JAND\DeployInstaller\Bootstrap
 */

namespace JAND\DeployInstaller;

require_once __DIR__.'/common/Autoload.inc';
\JAND\Common\Autoload::register();
Includes\DeployInstaller::start();
