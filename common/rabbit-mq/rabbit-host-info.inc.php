<?php

namespace JAND\Common\RabbitMq;

abstract class RabbitHostInfo
{
    /**
    @brief gets the currrent machine information and optionally any other task
    specific INI folder installed in the system path.
    Uses the default path of /var/system_ini/ unless $INIPATH is set

    @return parsed ini machine information
     */
    static function getHostInfo(array $extra = NULL)
    {
        $machine = array();
        if ($extra != NULL) {
            foreach ($extra as $ini) {
                $parsed = parse_ini_file($ini, true);
                if ($parsed) {
                    $machine = array_merge($machine, $parsed);
                }
            }
        }
        return $machine;
    }
}
