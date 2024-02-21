<?php

/**
 * Contains message for frontend to request login or registration.
 */


namespace JAND\Common\Messages\Frontend;

/**
 * A request from the frontend to login or register. Other classes are based on this.
 */
abstract class AccountRequest extends \JAND\Common\Messages\Request
{
  /** User's email. */
  private string $email;

  /** User's password. */
  private string $password;

  /**
   * Creates a new account request.
   * @param string $email User's email.
   * @param string $password User's password.
   * */
  public function __construct(string $email, string $password)
  {
    $this->email = $email;
    $this->password = $password;
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
   * Gets the user's password.
   * @return string User's password.
   */
  function getPassword()
  {
    return $this->password;
  }
}
