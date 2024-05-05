<?php
/**
 * RabbitMq client from Professor.
 *
 * @package JAND\Common\RabbitMq\RabbitMqClient
 */

namespace JAND\Common\RabbitMq;

/**
 * Client that sends requests to RabbitMq.
 */
class RabbitMqClient
{

    /**
     * Server config from ini file.
     *
     * @var mixed[] $machine Server config.
     */
    private array $machine;

    /**
     * AMQP host to connect to.
     *
     * @var string $brokerHost AMQP host.
     */
    private string $brokerHost;

    /**
     * AMQP broker port.
     *
     * @var integer $brokerPort AMQP broker port.
     */
    private int $brokerPort;

    /**
     * AMQP user.
     *
     * @var string $user AMQP user.
     */
    private string $user;

    /**
     * AMQP password.
     *
     * @var string $password AMQP password.
     */
    private string $password;

    /**
     * AMQP vhost.
     *
     * @var string $vHost AMQP vhost.
     */
    private string $vHost;

    /**
     * Name of exchange to send requests.
     *
     * @var string $serverExchangeName Name of exchange to send requests.
     */
    private string $serverExchangeName;

    /**
     * Each request gets its own queue for a response.
     * This is the prefix for each queue name.
     *
     * @var string $clientQueuePrefix Prefix of client queue name.
     */
    private string $clientQueuePrefix;

    /**
     * Array of responses with UID as key.
     * Populated by processResponse() and handled by
     * sendRequest().
     *
     * @var mixed[] Array of responses with message uid as key.
     */
    private array $responses;

    /**
     * Name of exchange to bind response queues.
     *
     * @var string $clientExchangeName Name of exchange to bind response ques.
     */
    private string $clientExchangeName;


      /**
       * Create new RabbitMq client.
       *
       * @param string $machine Path to ini file.
       * @param string $client  Name of client section.
       */
    public function __construct(string $machine, string $client)
    {
        $this->machine            = RabbitHostInfo::getHostInfo($machine);
        $this->brokerHost         = $this->machine[$client]['BROKER_HOST'];
        $this->brokerPort         = $this->machine[$client]['BROKER_PORT'];
        $this->user               = $this->machine[$client]['USER'];
        $this->password           = $this->machine[$client]['PASSWORD'];
        $this->vHost              = $this->machine[$client]['VHOST'];
        $this->serverExchangeName = $this->machine[$client]['SERVER_EXCHANGE'];
        $this->clientExchangeName = $this->machine[$client]['CLIENT_EXCHANGE'];
        $this->clientQueuePrefix  = $this->machine[$client]['CLIENT_QUEUE_PREFIX'];
        $this->responses          = [];

    }//end __construct()


    /**
     * Process response to a request. Sets the $responses array.
     *
     * @param \AMQPEnvelope $response      Response message.
     * @param \AMQPQueue    $responseQueue Queue response came in on.
     *
     * @return false False to hand control back to caller.
     */
    private function processResponse(\AMQPEnvelope $response, \AMQPQueue $responseQueue)
    {
        $uid = $response->getCorrelationId();

        $responseQueue->ack($response->getDeliveryTag());

        $this->responses[$uid] = $response->getBody();
        return false;

    }//end processResponse()


    /**
     * Sends a request to RabbitMq.
     *
     * @param mixed   $message     Message to send.
     * @param string  $contentType Message MIME type.
     * @param string  $routingKey  Routing key.
     * @param boolean $acceptReply Whether to accept replies.
     *
     * @return mixed Message response.
     *
     * @throws RabbitException Exception on timeout.
     */
    public function sendRequest(
        mixed $message,
        string $contentType='text/plain',
        string $routingKey='*',
        bool $acceptReply=true
    ) {
        $uid = uniqid();

        try {
            $params             = [];
            $params['host']     = $this->brokerHost;
            $params['port']     = $this->brokerPort;
            $params['login']    = $this->user;
            $params['password'] = $this->password;
            $params['vhost']    = $this->vHost;

            $conn = new \AMQPConnection($params);
            $conn->connect();

            $channel = new \AMQPChannel($conn);

            $exchange = new \AMQPExchange($channel);
            $exchange->setName($this->serverExchangeName);

            if ($acceptReply) {
                $responseQueue = new \AMQPQueue($channel);
                $responseQueue->setName($this->clientQueuePrefix.'.'.$uid);
                $responseQueue->setFlags(\AMQP_AUTODELETE);
                $responseQueue->declareQueue();
                $responseQueue->bind($this->clientExchangeName, $responseQueue->getName());
            }

            $publishFlags = [
                'content_type'   => $contentType,
                'correlation_id' => $uid,
            ];

            if ($acceptReply) {
                $publishFlags['reply_to'] = $responseQueue->getName();
            }

            $exchange->publish(
                $message,
                $routingKey,
                \AMQP_NOPARAM,
                $publishFlags
            );

            if (!$acceptReply) {
                return;
            }

            $response       = false;
            $waitIterations = 0;
            while ($response === false) {
                if ($waitIterations > 600) {
                    throw new RabbitException();
                }

                $response = $responseQueue->get();
                usleep(100000);
                $waitIterations++;
            }

            $responseQueue->ack($response->getDeliveryTag());
            return $response->getBody();
        } catch (\Exception $e) {
            die('failed to send message to exchange: '.$e->getMessage()."\n");
        }//end try

    }//end sendRequest()


}//end class
