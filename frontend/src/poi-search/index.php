<?php
/**
 * Loads the poi search page.
 *
 * @package JAND\Frontend\PoiSearch\Index
 */

namespace JAND\Frontend\PoiSearch;

require_once __DIR__.'/../common/Autoload.inc';
\JAND\Common\Autoload::register();

Includes\PoiSearch::processPoiSearch();
