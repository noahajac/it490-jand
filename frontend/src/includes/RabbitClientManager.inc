<?php
/**
 * Maintains a RabbitMq client for use in the frontend.
 *
 * @package JAND\Frontend\Includes\RabbitClientManager
 */

namespace JAND\Frontend\Includes;

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
                __DIR__.'/../rabbitmq.ini',
                'db-frontend_frontend.client'
            );
        }

        return static::$rabbitMqClient;

    }//end getClient()


}//end class
