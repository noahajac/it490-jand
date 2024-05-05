<?php
/**
 * Sends log messages.
 *
 * @package \JAND\DbConnector\Includes\LogSender
 */

namespace JAND\DbConnector\Includes;

use JAND\Common\Messages\Logger\LogMessageRequest;

/**
 * Sends log messages.
 */
abstract class LogSender
{


    /**
     * Send log message.
     *
     * @param string $message Message to send.
     *
     * @return void
     */
    public static function sendLog(string $message)
    {
        RabbitClientManager::sendLog(
            new LogMessageRequest(
                $message,
                gethostname(),
                new \DateTime()
            )
        );

    }//end sendLog()


}//end class
