#!/usr/bin/env php
<?php
/**
 * Bootstraps JAND database connector.
 *
 * @package JAND\DbConnector\Bootstrap
 */

namespace JAND\DbConnector;

require_once __DIR__.'/common/Autoload.inc';
\JAND\Common\Autoload::register();
Includes\Connector::start();
