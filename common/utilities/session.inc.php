<?php

namespace JAND\Common\Utilities;

class Session {
  private string $firstName;
  private string $lastName;
  private string $sessionToken;
  private int $sessionExpiration;

  function __construct(string $sessionToken, int $sessionExpiration, string $firstName, string $lastName)
  {
    $this->firstName = $firstName;
    $this->lastName = $lastName;
    $this->sessionToken = $sessionToken;
    $this->sessionExpiration = $sessionExpiration;
  }

  function getFirstName() {
    return $this->firstName;
  }

  function getLastName() {
    return $this->lastName;
  }

  function getFullName() {
    return $this->firstName . ' ' . $this->lastName;
  }

  function getSessionToken() {
    return $this->sessionToken;
  }

  function getSessionExpiration() {
    return $this->sessionExpiration;
  }
}
