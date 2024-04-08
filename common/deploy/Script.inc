<?php
/**
 * Enum of scripts for bundles.
 *
 * @package JAND\Common\Deploy\Script
 */

namespace JAND\Common\Deploy;

/**
 * Bundle scripts.
 */
enum Script: string
{
    case Rabbitmq = 'rabbitmq-deploy';
}//end enum
