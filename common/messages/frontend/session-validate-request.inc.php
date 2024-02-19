<?php
/**
 * Contains request definition for frontend to validate session tokens.
 */

namespace JAND\Common\Messages\Frontend;

/**
 * A request from the frontend to validate a session token.
 */
class SessionValidateRequest extends \JAND\Common\Messages\Request
{
  /** Token from user. */
  private string $sessionToken;

  /**
   * Creates a new login request.
   * @param string $sessionToken Token from user.
   * */
  public function __construct(string $sessionToken)
  {
    $this->sessionToken = $sessionToken;
  }

  /**
   * Gets the user's session token.
   * @return string User's session token.
   */
  function getSessionToken()
  {
    return $this->sessionToken;
  }
}
