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
    case Frontend    = 'jand-frontend';
    case DbConnector = 'jand-db-connector';
    case Dmz         = 'jand-dmz';
}//end enum
