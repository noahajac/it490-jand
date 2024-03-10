<?php
/**
 * Contains response from DB connector when validating a session.
 *
 * @package JAND\Common\Messages\Frontend\SessionValidateResponse
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Response from DB connector when validating a session.
 */
class SessionValidateResponse extends SessionResponse
{

    /**
     * Session object.
     *
     * @var ?\JAND\Common\Session $session User session object.
     */
    private ?\JAND\Common\Session $session;


    /**
     * Create a session validation response.
     *
     * @param boolean              $result  True for successful validation or invalidation,
     *  false if not valid or there is an error.
     * @param \JAND\Common\Session $session If no error, session object.
     */
    public function __construct(bool $result, ?\JAND\Common\Session $session=null)
    {
        parent::__construct($result);
        $this->session = $session;

    }//end __construct()


    /**
     * Get the session object.
     *
     * @return ?\JAND\Common\Session Session object.
     */
    public function getSession()
    {
        return $this->session;

    }//end getSession()


}//end class
