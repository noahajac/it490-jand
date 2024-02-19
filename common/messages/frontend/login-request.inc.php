<?php

/**
 * Contains message for frontend to request login.
 */


namespace JAND\Common\Messages\Frontend;

/**
 * A request from the frontend to login.
 */
class LoginRequest extends \JAND\Common\Messages\Request
{
  /** User's email. */
  private string $email;

  /** User's password hash. */
  private string $passwordHash;

  /**
   * Creates a new login request.
   * @param string $email User's email.
   * @param string $passwordHash User's password hash.
   * */
  public function __construct(string $email, string $passwordHash)
  {
    $this->email = $email;
    $this->passwordHash = $passwordHash;
  }

  /**
   * Gets the user's email.
   * @return string User's email.
   */
  function getEmail()
  {
    return $this->email;
  }

  /**
   * Gets the user's password hash.
   * @return string User's password hash.
   */
  function getPasswordHash()
  {
    return $this->passwordHash;
  }
}
