<?php

namespace JAND\Common\Messages\Frontend;

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

  public function getFirstName()
  {
    return $this->first_name;
  }

  public function getLastName()
  {
    return $this->last_name;
  }
}
