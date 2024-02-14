<?php


/**
 * This page contains the classes and enums used for messaging.
 */

namespace JAND {
  require_once('rabbitMQLib.inc.php');

  /** Base class for all requests. */
  abstract class Request
  {
    /**
     * Sends the request.
     * @param \rabbitMQClient $client RabbitMQ library client.
     * @return mixed Response from message broker.
     */
    public function send_request(\rabbitMQClient $client)
    {
      return unserialize(
        $client->send_request(serialize($this), 'application/php-serialized')
      );
    }
  }
}

namespace JAND\Frontend {
  /**
   * A request from the frontend to login.
   */
  class LoginRequest extends \JAND\Request
  {
    /** User's email. */
    private string $email;

    /** User's password hash. */
    private string $password_hash;

    /**
     * Creates a new login request.
     * @param string $email User's email.
     * @param string $password User's password hash.
     * */
    public function __construct(string $email, string $password_hash)
    {
      $this->email = $email;
      $this->password_hash = $password_hash;
    }

    /**
     * Gets the user's email.
     * @return string User's email.
     */
    function get_email()
    {
      return $this->email;
    }

    /**
     * Gets the user's password hash.
     * @return string User's password hash.
     */
    function get_password_hash()
    {
      return $this->password_hash;
    }
  }

  class LoginResponse
  {
    /** True for success, false for fail. */
    private bool $result;

    /** Session token. */
    private string $session_token;

    /** Unix timestamp of when the session expires. */
    private int $expiration;

    /**
     * Creates a new login response.
     * @param bool $result True if succesfully logged in, otherwise false.
     * @param string $session_token The session token.
     * @param int $expiration Unix timestamp of the session expiration. 
     */
    public function __construct(bool $result, string $session_token, int $expiration)
    {
      $this->result = $result;
      $this->session_token = $session_token;
      $this->expiration = $expiration;
    }

    /**
     * Gets login result.
     * @return bool True if success
     */
    function get_result()
    {
      return $this->result;
    }

    /**
     * Gets session token.
     * @return string Session token.
     */
    function get_session_token()
    {
      return $this->session_token;
    }

    /**
     * Gets session expiration.
     * @return int Expiration unix timestamp.
     */
    function get_expiration()
    {
      return $this->expiration;
    }
  }

  /**
   * A request from the frontend to register a new user.
   */
  class RegisterRequest extends LoginRequest
  {
    private string $first_name;
    private string $last_name;

    public function __construct(string $email, string $password, string $first_name, string $last_name)
    {
      parent::__construct($email, $password);
      $this->first_name = $first_name;
      $this->last_name = $last_name;
    }

    public function get_first_name()
    {
      return $this->first_name;
    }

    public function get_last_name()
    {
      return $this->last_name;
    }
  }
}
