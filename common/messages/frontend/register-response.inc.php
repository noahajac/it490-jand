<?php

/**
 * Contains response from DB connector when registering a new user.
 */

namespace JAND\Common\Messages\Frontend;

/**
 * DB connector response to a register request.
 */
class RegisterResponse extends LoginResponse {
  /** Error when there is a failure. */
  private ?RegisterError $error;

  /**
   * Create a new register response.
   * @param bool $result True on success, otherwise false.
   * @param ?\JAND\Common\Utilities\Session $session The session object on success.
   * @param ?RegisterError $error Error when registration is rejected.
   * */
  public function __construct(bool $result, ?\JAND\Common\Utilities\Session $session, ?RegisterError $error)
  {
    parent::__construct($result, $session);
    $this->error = $error;
  }

  /**
   * Gets registration error.
   * @return ?RegistrationError Registration error.
   */
  public function getError() {
    return $this->error;
  }
}
