<?php

namespace JAND\Common\RabbitMq;

class RabbitMqServer
{
	private $machine = "";
	public  $BROKER_HOST;
	private $BROKER_PORT;
	private $USER;
	private $PASSWORD;
	private $VHOST;
	private $exchange;
	private $queue;
	private $routing_key = '*';
	private $exchange_type = "topic";
	private $auto_delete = false;

	function __construct($machine, $server = "rabbitMQ")
	{
		$this->machine = RabbitHostInfo::getHostInfo(array($machine));
		$this->BROKER_HOST   = $this->machine[$server]["BROKER_HOST"];
		$this->BROKER_PORT   = $this->machine[$server]["BROKER_PORT"];
		$this->USER     = $this->machine[$server]["USER"];
		$this->PASSWORD = $this->machine[$server]["PASSWORD"];
		$this->VHOST = $this->machine[$server]["VHOST"];
		if (isset($this->machine[$server]["EXCHANGE_TYPE"])) {
			$this->exchange_type = $this->machine[$server]["EXCHANGE_TYPE"];
		}
		if (isset($this->machine[$server]["AUTO_DELETE"])) {
			$this->auto_delete = $this->machine[$server]["AUTO_DELETE"];
		}
		$this->exchange = $this->machine[$server]["EXCHANGE"];
		$this->queue = $this->machine[$server]["QUEUE"];
	}

	function process_message($msg)
	{
		// send the ack to clear the item from the queue
		if ($msg->getRoutingKey() !== "*") {
			return;
		}
		$this->conn_queue->ack($msg->getDeliveryTag());
		try {
			if ($msg->getReplyTo()) {
				// message wants a response
				// process request
				//$body = $msg->getBody();
				//$payload = json_decode($body, true);
				$payload = $msg->getBody();
				$response;
				if (isset($this->callback)) {
					$response = call_user_func($this->callback, $payload);
				}

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
				$exchange->setName($this->exchange);
				$exchange->setType($this->exchange_type);

				$conn_queue = new \AMQPQueue($channel);
				$conn_queue->setName($msg->getReplyTo());
				$replykey = $this->routing_key . ".response";
				$conn_queue->bind($exchange->getName(), $replykey);
				//$exchange->publish(json_encode($response),$replykey,AMQP_NOPARAM,array('correlation_id'=>$msg->getCorrelationId()));
				$exchange->publish($response, $replykey, \AMQP_NOPARAM, array('correlation_id' => $msg->getCorrelationId(), 'content_type' => $msg->getContentType()));

				return;
			}
		} catch (\Exception $e) {
			// ampq throws exception if get fails...
			echo "error: rabbitMQServer: process_message: exception caught: " . $e;
		}
		// message does not require a response, send ack immediately
		//$body = $msg->getBody();
		//$payload = json_decode($body, true);
		$payload = $msg->getBody();
		if (isset($this->callback)) {
			call_user_func($this->callback, $payload);
		}
		echo "processed one-way message\n";
	}

	function process_requests($callback)
	{
		try {
			$this->callback = $callback;
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
			$exchange->setName($this->exchange);
			$exchange->setType($this->exchange_type);

			$this->conn_queue = new \AMQPQueue($channel);
			$this->conn_queue->setName($this->queue);
			$this->conn_queue->bind($exchange->getName(), $this->routing_key);

			$this->conn_queue->consume(array($this, 'process_message'));

			// Loop as long as the channel has callbacks registered
			while (count($channel->callbacks)) {
				$channel->wait();
			}
		} catch (\Exception $e) {
			trigger_error("Failed to start request processor: " . $e, E_USER_ERROR);
		}
	}
}
