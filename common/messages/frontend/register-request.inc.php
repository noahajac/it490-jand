<?php

/**
 * Contains message for frontend to request a new user registration.
 */

namespace JAND\Common\Messages\Frontend;

/**
 * A request from the frontend to register a new user.
 */
class RegisterRequest extends AccountRequest
{
  /** User's first name. */
  private string $firstName;

  /** User's last name. */
  private string $lastName;

  /**
   * Creates a new register request.
   * @param string $email User's email.
   * @param string $password User's password.
   * @param string $firstName User's first name.
   * @param string $lastName User's last name.
   */
  public function __construct(string $email, string $password, string $firstName, string $lastName)
  {
    parent::__construct($email, $password);
    $this->firstName = $firstName;
    $this->lastName = $lastName;
  }

  /**
   * Gets the user's first name.
   * @return string User's first name.
   */
  public function getFirstName()
  {
    return $this->firstName;
  }

  /**
   * Gets the user's last name.
   * @return string User's last name.
   */
  public function getLastName()
  {
    return $this->lastName;
  }
}
