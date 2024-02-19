<?php

/**
 * Contains response from DB connector when validating a session.
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Response from DB connector when validating a session.
 */
class SessionValidateResponse
{
  /** True for successful validation, false if not valid. */
  private bool $result;

  /**
   * Gets validation result.
   * @return bool True for successful validation, false if not valid.
   */
  function getResult()
  {
    return $this->result;
  }
}
