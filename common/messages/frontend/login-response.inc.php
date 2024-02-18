<?php

namespace JAND\Common\Messages\Frontend;

class LoginResponse
  {
    /** True for success, false for fail. */
    private bool $result;

    /** Session token. */
    private ?string $session_token;

    /** Unix timestamp of when the session expires. */
    private ?int $expiration;

    /**
     * Creates a new login response.
     * @param bool $result True if succesfully logged in, otherwise false.
     * @param string $session_token The session token.
     * @param int $expiration Unix timestamp of the session expiration. 
     */
    public function __construct(bool $result, ?string $session_token, ?int $expiration)
    {
      $this->result = $result;
      $this->session_token = $session_token;
      $this->expiration = $expiration;
    }

    /**
     * Gets login result.
     * @return bool True if success
     */
    function getResult()
    {
      return $this->result;
    }

    /**
     * Gets session token.
     * @return string Session token.
     */
    function getSessionToken()
    {
      return $this->session_token;
    }

    /**
     * Gets session expiration.
     * @return int Expiration unix timestamp.
     */
    function getExpiration()
    {
      return $this->expiration;
    }
  }