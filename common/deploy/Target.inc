<?php
/**
 * Enum of targets for bundles.
 *
 * @package JAND\Common\Deploy\Target
 */

namespace JAND\Common\Deploy;

/**
 * Targets for bundles.
 */
enum Target: string
{
    case Frontend = 'frontend';
    case Backend  = 'backend';
    case Dmz      = 'dmz';
}//end enum
