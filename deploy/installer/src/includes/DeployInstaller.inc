<?php
/**
 * Contains main deploy installer logic.
 *
 * @package JAND\DeployInstaller\Includes\DeployInstaller
 */

namespace JAND\DeployInstaller\Includes;

/**
 * Listens to requests from Rabbit and performs appropriate
 * action.
 */
class DeployInstaller
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
        if ($request instanceof \JAND\Common\Messages\Deploy\InstallBundleRequest) {
            return Responders\InstallBundleResponder::respondToRequest($request);
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
            __DIR__.'/../rabbitmq.ini',
            'dinstallers-dserver_dinstallers.server'
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
