<?php

namespace JAND\Common\RabbitMq;

class RabbitMqClient
{
	private $machine = "";
	public  $BROKER_HOST;
	private $BROKER_PORT;
	private $USER;
	private $PASSWORD;
	private $VHOST;
	private $serverExchangeName;
	private $clientQueuePrefix;
	private $routing_key = '*';
	private $waitingResponses = array();
	private $clientQueue;
	private $clientExchangeName;
	//private $exchange_type = "topic";

	function __construct($machine, $server = "rabbitMQ")
	{
		$this->machine = RabbitHostInfo::getHostInfo(array($machine));
		$this->BROKER_HOST   = $this->machine[$server]["BROKER_HOST"];
		$this->BROKER_PORT   = $this->machine[$server]["BROKER_PORT"];
		$this->USER     = $this->machine[$server]["USER"];
		$this->PASSWORD = $this->machine[$server]["PASSWORD"];
		$this->VHOST = $this->machine[$server]["VHOST"];
		//if (isset($this->machine[$server]["EXCHANGE_TYPE"])) {
			//$this->exchange_type = $this->machine[$server]["EXCHANGE_TYPE"];
		//}
		//if (isset($this->machine[$server]["AUTO_DELETE"])) {
			//$this->auto_delete = $this->machine[$server]["AUTO_DELETE"];
		//}
		$this->serverExchangeName = $this->machine[$server]["SERVER_EXCHANGE"];
		$this->clientExchangeName = $this->machine[$server]["CLIENT_EXCHANGE"];
		$this->clientQueuePrefix = $this->machine[$server]["CLIENT_QUEUE_PREFIX"];
	}

	function process_response($response)
	{
		$uid = $response->getCorrelationId();
		if (!isset($this->waitingResponses[$uid])) {
			echo  "unknown uid\n";
			return true;
		}
		$this->clientQueue->ack($response->getDeliveryTag());
		//$body = $response->getBody();
		//$payload = json_decode($body, true);
		$payload = $response->getBody();
		if (!(isset($payload))) {
			$payload = "[empty response]";
		}
		$this->waitingResponses[$uid] = $payload;
		return false;
	}

	function send_request($message, $content_type = 'text/plain')
	{
		$uid = uniqid();

		//$json_message = json_encode($message);
		try {
			$params = array();
			$params['host'] = $this->BROKER_HOST;
			$params['port'] = $this->BROKER_PORT;
			$params['login'] = $this->USER;
			$params['password'] = $this->PASSWORD;
			$params['vhost'] = $this->VHOST;

			$conn = new \AMQPConnection($params);
			$conn->connect();

			$channel = new \AMQPChannel($conn);

			$exchange = new \AMQPExchange($channel);
			$exchange->setName($this->serverExchangeName);
			//$exchange->setType($this->exchange_type);

			$this->clientQueue = new \AMQPQueue($channel);
			$this->clientQueue->setName($this->clientQueuePrefix . '.' . $uid);
			$this->clientQueue->setFlags(\AMQP_AUTODELETE);
			$this->clientQueue->declare();
			$this->clientQueue->bind($this->clientExchangeName, $this->clientQueue->getName());

			//$this->conn_queue = new \AMQPQueue($channel);
			//$this->conn_queue->setName($this->queue);
			//$this->conn_queue->bind($exchange->getName(), $this->routing_key);

			//$exchange->publish($json_message,$this->routing_key,AMQP_NOPARAM,array('reply_to'=>$callback_queue->getName(),'content_type'=>'application/json','correlation_id'=>$uid));
			$exchange->publish($message, $this->routing_key, \AMQP_NOPARAM, array('reply_to' => $this->clientQueue->getName(), 'content_type' => $content_type, 'correlation_id' => $uid));
			$this->waitingResponses[$uid] = "waiting";
			$this->clientQueue->consume(array($this, 'process_response'));

			$response = $this->waitingResponses[$uid];
			unset($this->waitingResponses[$uid]);
			return $response;
		} catch (\Exception $e) {
			die("failed to send message to exchange: " . $e->getMessage() . "\n");
		}
	}

	/**
	  @brief send a one-way message to the server.  These are
	  auto-acknowledged and give no response.

	  @param message the body of the request.  This must make sense to the
	  server
	 */
	function publish($message, $content_type = 'text/plain')
	{
		//$json_message = json_encode($message);
		try {
			$params = array();
			$params['host'] = $this->BROKER_HOST;
			$params['port'] = $this->BROKER_PORT;
			$params['login'] = $this->USER;
			$params['password'] = $this->PASSWORD;
			$params['vhost'] = $this->VHOST;
			$conn = new \AMQPConnection($params);
			$conn->connect();
			$channel = new \AMQPChannel($conn);
			$exchange = new \AMQPExchange($channel);
			$exchange->setName($this->serverExchangeName);
			//$exchange->setType($this->exchange_type);
			//$this->conn_queue = new \AMQPQueue($channel);
			//$this->conn_queue->setName($this->queue);
			//$this->conn_queue->bind($exchange->getName(), $this->routing_key);
			//return $exchange->publish($json_message,$this->routing_key);
			return $exchange->publish($message, $this->routing_key, \AMQP_NOPARAM, array('content_type' => $content_type));
		} catch (\Exception $e) {
			die("failed to send message to exchange: " . $e->getMessage() . "\n");
		}
	}
}
