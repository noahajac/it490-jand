<?php

/**
 * Contains response from DB connector when validating a session.
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Response from DB connector when validating a session.
 */
class SessionValidateResponse extends SessionResponse
{
  /** Session object. */
  private ?\JAND\Common\Utilities\Session $session;

  /**
   * Create a session validation response.
   * @param bool $result True for successful validation or invalidation, false if not valid or there is an error.
   * @param ?\JAND\Common\Utilities\Session If no error, session object.
   */
  function __construct(bool $result, ?\JAND\Common\Utilities\Session $session = null)
  {
    parent::__construct($result);
    $this->session = $session;
  }

  /**
   * Get the session object.
   * @return ?\JAND\Common\Utilities\Session Session object.
   */
  function getSession() {
    return $this->session;
  }
}
