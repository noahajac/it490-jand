<?php

namespace JAND;

enum FrontendRequests
{
  case login;
  case register;
  case session_check;
}

class FrontendRequest
{
  private FrontendRequests $type;
  private string $email;
  private string $password;

  function __construct(FrontendRequests $type)
  {
    $this->type = $type;
  }

  function set_email($email) {
    $this->email = $email;
  }

  function set_password($password) {
    $this->password = $password;
  }
}
