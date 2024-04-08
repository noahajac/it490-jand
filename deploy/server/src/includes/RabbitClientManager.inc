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
     * RabbitMq client instance for bundlers.
     *
     * @var ?\JAND\Common\RabbitMq\RabbitMqClient $rabbitMqClientBundlers RabbitMq client instance.
     */
    private static ?\JAND\Common\RabbitMq\RabbitMqClient $rabbitMqClientBundlers;

    /**
     * RabbitMq client instance for installers.
     *
     * @var ?\JAND\Common\RabbitMq\RabbitMqClient $rabbitMqClientInstallers RabbitMq client instance.
     */
    private static ?\JAND\Common\RabbitMq\RabbitMqClient $rabbitMqClientInstallers;


    /**
     * Gets RabbitMq client for bundlers.
     *
     * @return \JAND\Common\RabbitMq\RabbitMqClient RabbitMq client.
     */
    public static function getBundlerClient()
    {
        if (!isset(static::$rabbitMqClientBundlers)) {
            static::$rabbitMqClientBundlers = new \JAND\Common\RabbitMq\RabbitMqClient(
                __DIR__.'/../rabbitmq.ini',
                'dbundlers-dserver_dserver.client'
            );
        }

        return static::$rabbitMqClientBundlers;

    }//end getBundlerClient()


    /**
     * Gets RabbitMq client for installers.
     *
     * @return \JAND\Common\RabbitMq\RabbitMqClient RabbitMq client.
     */
    public static function getInstallerClient()
    {
        if (!isset(static::$rabbitMqClientInstallers)) {
            static::$rabbitMqClientInstallers = new \JAND\Common\RabbitMq\RabbitMqClient(
                __DIR__.'/../rabbitmq.ini',
                'dinstallers-dserver_dserver.client'
            );
        }

        return static::$rabbitMqClientInstallers;

    }//end getInstallerClient()


}//end class
