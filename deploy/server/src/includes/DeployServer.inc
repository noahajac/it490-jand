<?php
/**
 * Contains main deploy server logic.
 *
 * @package JAND\DeployServer\Includes\DeployServer
 */

namespace JAND\DeployServer\Includes;

/**
 * Listens to requests from Rabbit and performs appropriate
 * action./
 */
class DeployServer
{

    /**
     * RabbitMqServer instance.
     *
     * @var \JAND\Common\RabbitMq\RabbitMqServer $server RabbitMQ server.
     */
    private static \JAND\Common\RabbitMq\RabbitMqServer $server;

    /**
     * Database PDO instance.
     *
     * @var \PDO $pdo PDO instance.
     */
    private static \PDO $pdo;


    /**
     * Requests from the message broker get processed here.
     *
     * @param mixed $request The request.
     *
     * @return mixed Request response, false if unknown.
     */
    private static function requestProcessor(mixed $request)
    {
        if ($request instanceof \JAND\Common\Messages\Deploy\GetBundleTypesRequest) {
            return Responders\GetBundleTypesResponder::respondToRequest();
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
            'dclient-dserver_dserver.server'
        );

        $dsn         = 'mysql:unix_socket=/var/run/mysqld/mysqld.sock;dbname=jand_deploy;charset=utf8';
        static::$pdo = new \PDO($dsn, 'jand');
        static::$pdo->setAttribute(\PDO::ATTR_ERRMODE, \PDO::ERRMODE_EXCEPTION);
        static::$pdo->setAttribute(\PDO::ATTR_EMULATE_PREPARES, true);
        static::$server->processRequests(
            function (string $requestString) {
                return serialize(
                    static::requestProcessor(unserialize($requestString))
                );
            }
        );

    }//end start()


}//end class
