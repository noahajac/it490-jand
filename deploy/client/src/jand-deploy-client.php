#!/usr/bin/env php
<?php
/**
 * Bootstraps JAND deploy client.
 *
 * @package JAND\DeployClient\Bootstrap
 */

namespace JAND\DeployClient;

require_once __DIR__.'/common/Autoload.inc';
\JAND\Common\Autoload::register();
Includes\DeployClient::start($argv);
