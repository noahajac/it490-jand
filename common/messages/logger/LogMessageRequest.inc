<?php
/**
 * Contains new message to log.
 *
 * @package JAND\Common\Messages\Logger\LogMessageRequest
 */

namespace JAND\Common\Messages\Logger;

/**
 * A request from the deploy client to get bundles.
 */
class LogMessageRequest extends \JAND\Common\Messages\Request
{

    /**
     * Message to log.
     *
     * @var string $message Message to log.
     */
    private string $message;

    /**
     * Timestamp of message.
     *
     * @var \DateTime $timestamp Message timestamp.
     */
    private \DateTime $timestamp;

    /**
     * Source of message.
     *
     * @var string $source Message sender.
     */
    private string $source;


    /**
     * Create a new log message request.
     *
     * @param string    $message   The message.
     * @param string    $source    Message source.
     * @param \DateTime $timestamp Message timestamp.
     */
    public function __construct(string $message, string $source, \DateTime $timestamp)
    {
        $this->message   = $message;
        $this->source    = $source;
        $this->timestamp = $timestamp;

    }//end __construct()


    /**
     * Gets the message.
     *
     * @return string The message.
     */
    public function getMessage()
    {
        return $this->message;

    }//end getMessage()


    /**
     * Get the source.
     *
     * @return string Message sender.
     */
    public function getSource()
    {
        return $this->source;

    }//end getSource()


    /**
     * Get the timestamp.
     *
     * @return \DateTime Message timestamp.
     */
    public function getTimestamp()
    {
        return $this->timestamp;

    }//end getTimestamp()


}//end class
