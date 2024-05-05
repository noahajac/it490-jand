<?php
/**
 * Sends message to DB connector to run timer events.
 *
 * @package JAND\DbTimer\Includes\Connector
 */

namespace JAND\DbTimer\Includes;

use JAND\Common\Messages\DbTimer\RunEventsRequest;

/**
 * When program runs, imitates frontend and tells DB connector to run
 * timed events.
 */
class Timer
{


    /**
     * Send message to DB connector to run timer events.
     *
     * @return void
     */
    public static function start()
    {
        if (shell_exec('systemctl is-active jand-db-connector.service') === 'active'.PHP_EOL) {
            RabbitClientManager::sendRequest(new RunEventsRequest());
        }

        exit(0);

    }//end start()


}//end class
