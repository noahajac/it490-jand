<?php
/**
 * Enum of targets for rollback.
 *
 * @package JAND\Common\Deploy\RollbackTarget
 */

namespace JAND\Common\Deploy;

/**
 * Targets for bundles.
 */
enum RollbackTarget: string
{
    case Qa   = 'qa';
    case Prod = 'prod';
}//end enum
