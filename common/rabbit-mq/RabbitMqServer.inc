<?php
/**
 * RabbitMq server from Professor.
 *
 * @package JAND\Common\RabbitMq\RabbitMqServer
 */

namespace JAND\Common\RabbitMq;

/**
 * Server that listens for requests through RabbitMq.
 */
class RabbitMqServer
{

    /**
     * Server config from ini file.
     *
     * @var mixed[] $machine Server config.
     */
    private array $machine;

    /**
     * Callback function to run when requests are received.
     *
     * @var callable $callback Function to run when requests are received.
     */
    private \Closure $callback;

    /**
     * RabbitMq connection.
     *
     * @var \AMQPConnection $conn RabbitMq connection.
     */
    private \AMQPConnection $conn;

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
     * Name of exchange to send client responses.
     *
     * @var string $clientExchangeName Name of exchange to send reponses.
     */
    private string $clientExchangeName;

    /**
     * Only process requests if this file doesn't exists.
     *
     * @var string $inhibitFile Don't process request if this file exists.
     */
    private ?string $inhibitFile;

    /**
     * AMQP server queue.
     *
     * @var \AMQPQueue $serverQueue Server queue to receive requests.
     */
    private \AMQPQueue $serverQueue;

    /**
     * Server queue name.
     *
     * @var string $serverQueueName Name of queue to receive requests.
     */
    private string $serverQueueName;


    /**
     * Create a new RabbitMq server.
     *
     * @param string $machine Path to ini file.
     * @param string $server  Name of server section.
     */
    public function __construct(string $machine, string $server)
    {
        $this->machine            = RabbitHostInfo::getHostInfo($machine);
        $this->brokerHost         = $this->machine[$server]['BROKER_HOST'];
        $this->brokerPort         = $this->machine[$server]['BROKER_PORT'];
        $this->user               = $this->machine[$server]['USER'];
        $this->password           = $this->machine[$server]['PASSWORD'];
        $this->vHost              = $this->machine[$server]['VHOST'];
        $this->clientExchangeName = $this->machine[$server]['CLIENT_EXCHANGE'];
        $this->serverQueueName    = $this->machine[$server]['SERVER_QUEUE'];

    }//end __construct()


    /**
     * Process a message from the queue.
     *
     * @param \AMQPEnvelope $msg Message to process.
     *
     * @return boolean Success or failure.
     */
    public function processMessage(\AMQPEnvelope $msg)
    {
        if (isset($this->inhibitFile) && file_exists($this->inhibitFile)) {
            return true;
        }

        // Send the ack to clear the item from the queue.
        $this->serverQueue->ack($msg->getDeliveryTag());
        try {
            if ($msg->getReplyTo()) {
                // Message wants a response. Process request.
                $payload = $msg->getBody();

                if (isset($this->callback)) {
                    $response = call_user_func($this->callback, $payload);
                }

                $channel  = new \AMQPChannel($this->conn);
                $exchange = new \AMQPExchange($channel);

                $exchange->setName($this->clientExchangeName);
                $exchange->publish(
                    $response,
                    $msg->getReplyTo(),
                    \AMQP_NOPARAM,
                    [
                        'correlation_id' => $msg->getCorrelationId(),
                        'content_type'   => $msg->getContentType(),
                    ]
                );

                return true;
            } else {
                // Message does not require a response, send ack immediately.
                $payload = $msg->getBody();
                if (isset($this->callback)) {
                    call_user_func($this->callback, $payload);
                }
            }//end if
        } catch (\Exception $e) {
            // Ampq throws exception if get fails.
            echo 'JAND DB Connector failed to process a message: '.$e;
        }//end try

    }//end processMessage()


    /**
     * Connect to RabbitMQ server and start processing requests.
     *
     * @param callable $callback    Callback function when a request comes in.
     * @param string   $inhibitFile If set, don't process message when file exists.
     *
     * @return void
     */
    public function processRequests(callable $callback, ?string $inhibitFile=null)
    {
        try {
            $this->inhibitFile  = $inhibitFile;
            $this->callback     = $callback;
            $params             = [];
            $params['host']     = $this->brokerHost;
            $params['port']     = $this->brokerPort;
            $params['login']    = $this->user;
            $params['password'] = $this->password;
            $params['vhost']    = $this->vHost;
            $this->conn         = new \AMQPConnection($params);
            $this->conn->connect();

            $channel = new \AMQPChannel($this->conn);

            $this->serverQueue = new \AMQPQueue($channel);
            $this->serverQueue->setName($this->serverQueueName);
            $this->serverQueue->consume([$this, 'processMessage']);
        } catch (\Exception $e) {
            trigger_error('Failed to start request processor: '.$e, E_USER_ERROR);
        }//end try

    }//end processRequests()


}//end class
