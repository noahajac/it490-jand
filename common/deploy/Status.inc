<?php
/**
 * Enum of status for bundles.
 *
 * @package JAND\Common\Deploy\Status
 */

namespace JAND\Common\Deploy;

/**
 * Bundle status.
 */
enum Status: int
{
    case New    = 0;
    case Failed = 1;
    case Passed = 2;
}//end enum
