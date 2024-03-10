<?php
/**
 * Initially from Professor.
 * Gets RabbitMQ config from ini file.
 *
 * @package JAND\Common\RabbitMq\RabbitHostInfo
 */

namespace JAND\Common\RabbitMq;

/**
 * Initially from Professor.
 * Gets RabbitMQ config from ini file.
 */
abstract class RabbitHostInfo
{


    /**
     * Gets the currrent machine information and optionally any other task
     * specific INI folder installed in the system path.
     *
     * @param string $iniFile Name of ini file.
     *
     * @return array Parsed ini machine information.
     */
    public static function getHostInfo(string $iniFile)
    {
        $machine = [];
        $parsed  = parse_ini_file($iniFile, true);
        if ($parsed) {
            $machine = array_merge($machine, $parsed);
        }

        return $machine;

    }//end getHostInfo()


}//end class
