<?php

namespace JAND\Common\Messages\Frontend;

class RegisterResponse extends LoginResponse {
  private ?RegisterError $error;

  public function __construct(bool $result, ?string $session_token, ?int $expiration, ?RegisterError $error)
  {
    parent::__construct($result, $session_token, $expiration);
    $this->error = $error;
  }

  public function getError() {
    return $this->error;
  }
}
