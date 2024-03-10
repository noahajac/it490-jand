<?php
/**
 * Contains response from DB connector when handling session messages.
 *
 * @package JAND\Common\Messages\Frontend\SessionResonse
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Response from DB connector when handling session messages. Other classes are based on this.
 */
abstract class SessionResponse
{

    /**
     * True for successful validation or invalidation, false if not valid or there is an error.
     *
     * @var boolean $result Success or failure.
     */
    private bool $result;


    /**
     * Create new session response.
     *
     * @param boolean $result True for successful validation or invalidation, false if not valid or there is an error.
     */
    public function __construct(bool $result)
    {
        $this->result = $result;

    }//end __construct()


    /**
     * Gets result.
     *
     * @return boolean True for successful validation or invalidation, false if not valid or there is an error.
     */
    public function getResult()
    {
        return $this->result;

    }//end getResult()


}//end class
