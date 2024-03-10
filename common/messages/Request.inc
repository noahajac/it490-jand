<?php
/**
 * Contains request base class.
 *
 * @package JAND\Common\Messages\Request
 */

namespace JAND\Common\Messages;

/**
 * Base class for all requests.
 */
abstract class Request
{


    /**
     * Sends the request.
     *
     * @param \JAND\Common\RabbitMq\RabbitMqClient $client RabbitMQ library client.
     *
     * @return mixed Response from message broker.
     */
    public function sendRequest(\JAND\Common\RabbitMq\RabbitMqClient $client)
    {
        return unserialize(
            $client->sendRequest(serialize($this), 'application/php-serialized')
        );

    }//end sendRequest()


}//end class
