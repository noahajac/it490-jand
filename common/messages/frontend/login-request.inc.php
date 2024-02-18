<?php

namespace JAND\Common\Messages\Frontend;

/**
 * A request from the frontend to login.
 */
class LoginRequest extends \JAND\Common\Messages\Request
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
    return $this->password_hash;
  }
}
