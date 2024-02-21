<?php

/**
 * Contains response from DB connector for a login request.
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Response from DB connector for a login request.
 */
class LoginResponse
{
  /** True for success, false for fail. */
  private bool $result;

  /** Session object. */
  private ?\JAND\Common\Utilities\Session $session;

  /**
   * Creates a new login response.
   * @param bool $result True if succesfully logged in, otherwise false.
   * @param \JAND\Common\Utilities\Session $session The session object.
   */
  public function __construct(bool $result, ?\JAND\Common\Utilities\Session $session)
  {
    $this->result = $result;
    $this->session = $session;
  }

  /**
   * Gets login result.
   * @return bool True if success.
   */
  function getResult()
  {
    return $this->result;
  }

  /**
   * Gets session.
   * @return ?\JAND\Common\Utilities\Session Session object.
   */
  function getSession()
  {
    return $this->session;
  }
}
