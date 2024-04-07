<?php
/**
 * Maintains a RabbitMq client.
 *
 * @package JAND\DeployClient\Includes\RabbitClientManager
 */

namespace JAND\DeployClient\Includes;

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
                'dclient-dserver_dclient.client'
            );
        }

        return static::$rabbitMqClient;

    }//end getClient()


}//end class
