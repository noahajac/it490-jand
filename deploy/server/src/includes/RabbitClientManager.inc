<?php
/**
 * Maintains a RabbitMq client.
 *
 * @package JAND\DeployServer\Includes\RabbitClientManager
 */

namespace JAND\DeployServer\Includes;

/**
 * RabbitMq client manager.
 */
abstract class RabbitClientManager
{

    /**
     * RabbitMq client instance.
     *
     * @var ?\JAND\Common\RabbitMq\RabbitMqClient $rabbitMqClient RabbitMq client instance.
     */
    private static ?\JAND\Common\RabbitMq\RabbitMqClient $rabbitMqClient;


    /**
     * Gets RabbitMq client.
     *
     * @return \JAND\Common\RabbitMq\RabbitMqClient RabbitMq client.
     */
    public static function getClient()
    {
        if (!isset(static::$rabbitMqClient)) {
            static::$rabbitMqClient = new \JAND\Common\RabbitMq\RabbitMqClient(
                __DIR__.'/rabbitmq.ini',
                'dserver-dworkers_dserver.client'
            );
        }

        return static::$rabbitMqClient;

    }//end getClient()


}//end class
