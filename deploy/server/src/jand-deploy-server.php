#!/usr/bin/env php
<?php
/**
 * Bootstraps JAND deploy server.
 *
 * @package JAND\DeployServer\Bootstrap
 */

namespace JAND\DeployServer;

require_once __DIR__.'/common/Autoload.inc';
\JAND\Common\Autoload::register();
Includes\DeployServer::start();
