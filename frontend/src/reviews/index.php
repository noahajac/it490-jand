<?php
/**
 * Loads the reviews page.
 *
 * @package JAND\Frontend\Reviews\Index
 */

namespace JAND\Frontend\Reviews;

require_once __DIR__.'/../common/Autoload.inc';
\JAND\Common\Autoload::register();

Includes\Reviews::processReviews();
