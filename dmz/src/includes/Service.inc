<?php
/**
 * Contains main DMZ service logic.
 *
 * @package JAND\Dmz\Includes\Service
 */

namespace JAND\Dmz\Includes;

/**
 * Listens to requests from Rabbit and makes the appropriate
 * API queries to craft a response.
 */
class Service
{

    /**
     * RabbitMqServer instance.
     *
     * @var \JAND\Common\RabbitMq\RabbitMqServer $server RabbitMQ server.
     */
    private static \JAND\Common\RabbitMq\RabbitMqServer $server;


    /**
     * Requests from the message broker get processed here.
     *
     * @param mixed $request The request.
     *
     * @return mixed Request response, false if unknown.
     */
    private static function requestProcessor(mixed $request)
    {
        if ($request instanceof \JAND\Common\Messages\Shared\AirportCitySearchRequest) {
            return Responders\AirportCitySearchResponder::respondToRequest($request);
        } else {
            return false;
        }//end if

    }//end requestProcessor()


    /**
     * Creates RabbitMqServer and PDO, then starts listening to requests.
     *
     * @return void
     */
    public static function start()
    {
        static::$server = new \JAND\Common\RabbitMq\RabbitMqServer(
            __DIR__.'/rabbitmq.ini',
            'db-dmz_dmz.server'
        );

        static::$server->processRequests(
            function (string $requestString) {
                return serialize(
                    static::requestProcessor(unserialize($requestString))
                );
            }
        );

    }//end start()


}//end class