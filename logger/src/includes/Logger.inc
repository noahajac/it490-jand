<?php
/**
 * Listens to logs from Rabbit and writes them to disk.
 *
 * @package JAND\Logger\Includes\Service
 */

namespace JAND\Logger\Includes;

use JAND\Common\Messages\Logger\LogMessageRequest;

/**
 * Listens to logs from Rabbit and writes them to disk.
 */
class Logger
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
     * @return void
     */
    private static function requestProcessor(mixed $request)
    {
        if (!($request instanceof LogMessageRequest)) {
            return;
        }

        $fileHandle = fopen('/var/log/jand.log', 'a');

        $message  = '['.$request->getTimestamp()->format('Y-m-d H:i:s').'] ('.$request->getSource().') ';
        $message .= $request->getMessage().PHP_EOL;

        fwrite(
            $fileHandle,
            $message
        );

        fclose($fileHandle);

    }//end requestProcessor()


    /**
     * Creates RabbitMqServer and PDO, then starts listening to requests.
     *
     * @return void
     */
    public static function start()
    {
        static::$server = new \JAND\Common\RabbitMq\RabbitMqServer(
            __DIR__.'/../rabbitmq.ini',
            'logger_logger.server.frontend'
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
