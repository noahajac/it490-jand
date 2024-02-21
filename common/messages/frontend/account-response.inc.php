<?php

/**
 * Contains response from DB connector for an account request.
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Response from DB connector for an account request.
 */
abstract class AccountResponse
{
  /** True for success, false for fail. */
  private bool $result;

  /** Session object. */
  private ?\JAND\Common\Utilities\Session $session;

  /**
   * Creates a new account response.
   * @param bool $result True if succesfully logged in, otherwise false.
   * @param \JAND\Common\Utilities\Session $session The session object.
   */
  public function __construct(bool $result, ?\JAND\Common\Utilities\Session $session = null)
  {
    $this->result = $result;
    $this->session = $session;
  }

  /**
   * Gets login/registration result.
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
