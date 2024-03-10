<?php
/**
 * Contains request definition for frontend session messages.
 *
 * @package JAND\Common\Messages\Frontend\SessionRequest
 */

namespace JAND\Common\Messages\Frontend;

/**
 * A request from the frontend for a session operation. Other classes are based on this.
 */
abstract class SessionRequest extends \JAND\Common\Messages\Request
{

    /**
     * Token from user.
     *
     * @var string $sessionToken Session token from user.
     */
    private string $sessionToken;


    /**
     * Creates a new session request.
     *
     * @param string $sessionToken Token from user.
     * */
    public function __construct(string $sessionToken)
    {
        $this->sessionToken = $sessionToken;

    }//end __construct()


    /**
     * Gets the user's session token.
     *
     * @return string User's session token.
     */
    public function getSessionToken()
    {
        return $this->sessionToken;

    }//end getSessionToken()


}//end class
