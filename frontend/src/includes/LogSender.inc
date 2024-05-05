<?php
/**
 * Sends log messages.
 *
 * @package \JAND\Frontend\Includes\LogSender
 */

namespace JAND\Frontend\Includes;

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
