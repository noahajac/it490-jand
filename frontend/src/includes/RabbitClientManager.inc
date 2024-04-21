<?php
/**
 * Maintains a RabbitMq client for use in the frontend.
 *
 * @package JAND\Frontend\Includes\RabbitClientManager
 */

namespace JAND\Frontend\Includes;

use JAND\Common\Messages\Request;

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
     * @param boolean $force Force reconnecting.
     *
     * @return \JAND\Common\RabbitMq\RabbitMqClient RabbitMq client.
     */
    public static function getClient(bool $force=false)
    {
        if (!isset(static::$rabbitMqClient) || $force) {
            static::$rabbitMqClient = new \JAND\Common\RabbitMq\RabbitMqClient(
                __DIR__.'/../rabbitmq.ini',
                'db-frontend_frontend.client'
            );
        }

        return static::$rabbitMqClient;

    }//end getClient()


    /**
     * Sends a request.
     *
     * @param Request $request    Request to send.
     * @param string  $routingKey Routing key.
     *
     * @return ResponseType Response from message broker.
     */
    public static function sendRequest(Request $request, string $routingKey='*')
    {
        try {
            static::getClient();
            $request = static::$rabbitMqClient->sendRequest(
                serialize($request),
                'application/php-serialized',
                $routingKey
            );
        } catch (\Throwable $th) {
            // Try twice.
            try {
                static::getClient(true);
                $request = static::$rabbitMqClient->sendRequest(
                    serialize($request),
                    'application/php-serialized',
                    $routingKey
                );
            } catch (\Throwable $th) {
                echo 'An error has occured. Try again or contact an administrator if this is reoccuring.';
                exit();
            }
        }//end try

        return unserialize(
            $request
        );

    }//end sendRequest()


}//end class
