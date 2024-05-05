<?php
/**
 * Maintains a RabbitMq client for use in the DMZ connector.
 *
 * @package JAND\Dmz\Includes\RabbitClientManager
 */

namespace JAND\Dmz\Includes;

use JAND\Common\Messages\Logger\LogMessageRequest;
use JAND\Common\Messages\Request;

/**
 * RabbitMq client manager.
 */
abstract class RabbitClientManager
{

    /**
     * RabbitMq logger client instance.
     *
     * @var ?\JAND\Common\RabbitMq\RabbitMqClient $rabbitMqLoggerClient RabbitMq logger client instance.
     */
    private static ?\JAND\Common\RabbitMq\RabbitMqClient $rabbitMqLoggerClient;


    /**
     * Gets RabbitMq logger client.
     *
     * @param boolean $force Force reconnecting.
     *
     * @return \JAND\Common\RabbitMq\RabbitMqClient RabbitMq client.
     */
    public static function getLoggerClient(bool $force=false)
    {
        if (!isset(static::$rabbitMqLoggerClient) || $force) {
            static::$rabbitMqLoggerClient = new \JAND\Common\RabbitMq\RabbitMqClient(
                __DIR__.'/../rabbitmq.ini',
                'logger_logger.client.dmz'
            );
        }

        return static::$rabbitMqLoggerClient;

    }//end getLoggerClient()


    /**
     * Sends a request.
     *
     * @param LogMessageRequest $request Log to send.
     *
     * @return void
     */
    public static function sendLog(LogMessageRequest $request)
    {
        try {
            static::getLoggerClient();
            $request = static::$rabbitMqLoggerClient->sendRequest(
                serialize($request),
                'application/php-serialized',
                '*',
                false
            );
        } catch (\Throwable $th) {
            // Try twice.
            try {
                static::getLoggerClient(true);
                $request = static::$rabbitMqLoggerClient->sendRequest(
                    serialize($request),
                    'application/php-serialized',
                    '*',
                    false
                );
            } catch (\Throwable $th) {
                echo $th;
                echo 'An error has occured. Try again or contact an administrator if this is reoccuring.';
                exit();
            }
        }//end try

    }//end sendLog()


}//end class
