#!/usr/bin/env php
<?php
/**
 * Bootstraps JAND deploy bundler daemon.
 *
 * @package JAND\DeployServer\Bootstrap
 */

namespace JAND\DeployBundler;

require_once __DIR__.'/common/Autoload.inc';
\JAND\Common\Autoload::register();
Includes\DeployBundler::start();
