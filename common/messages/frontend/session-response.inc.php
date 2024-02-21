<?php

/**
 * Contains response from DB connector when handling session messages.
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Response from DB connector when handling session messages. Other classes are based on this.
 */
abstract class SessionResponse
{
  /** True for successful validation or invalidation, false if not valid or there is an error. */
  private bool $result;


  /**
   * Create new session response.
   * @param bool $result True for successful validation or invalidation, false if not valid or there is an error.
   */
  function __construct(bool $result)
  {
    $this->result = $result;
  }

  /**
   * Gets result.
   * @return bool True for successful validation or invalidation, false if not valid or there is an error.
   */
  function getResult()
  {
    return $this->result;
  }
}
