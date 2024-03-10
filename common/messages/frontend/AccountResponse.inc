<?php
/**
 * Contains response from DB connector for an account request.
 *
 * @package JAND\Common\Messages\Frontend\AccountResponse
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Response from DB connector for an account request.
 */
abstract class AccountResponse
{

    /**
     * True for success, false for fail.
     *
     * @var boolean $result Success or fail.
     */
    private bool $result;

    /**
     * Session object.
     *
     * @var ?\JAND\Common\Session $session User session object.
     */
    private ?\JAND\Common\Session $session;


    /**
     * Creates a new account response.
     *
     * @param boolean              $result  True if succesfully logged in, otherwise false.
     * @param \JAND\Common\Session $session The session object.
     */
    public function __construct(bool $result, ?\JAND\Common\Session $session=null)
    {
        $this->result  = $result;
        $this->session = $session;

    }//end __construct()


    /**
     * Gets login/registration result.
     *
     * @return boolean True if success.
     */
    public function getResult()
    {
        return $this->result;

    }//end getResult()


    /**
     * Gets session.
     *
     * @return ?\JAND\Common\Session Session object.
     */
    public function getSession()
    {
        return $this->session;

    }//end getSession()


}//end class
