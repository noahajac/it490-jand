<?php
/**
 * Contains main deploy bundler logic.
 *
 * @package JAND\DeployBundler\Includes\DeployBundler
 */

namespace JAND\DeployBundler\Includes;

/**
 * Listens to requests from Rabbit and performs appropriate
 * action.
 */
class DeployBundler
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
        if ($request instanceof \JAND\Common\Messages\Deploy\CreateNewBundleRequest) {
            return Responders\CreateNewBundleResponder::respondToRequest($request);
        } else {
            return false;
        }//end if

    }//end requestProcessor()


    /**
     * Creates RabbitMqServer, then starts listening to requests.
     *
     * @return void
     */
    public static function start()
    {
        static::$server = new \JAND\Common\RabbitMq\RabbitMqServer(
            __DIR__.'/rabbitmq.ini',
            'dbundlers-dserver_dbundlers.server'
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
