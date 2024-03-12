<?php
/**
 * Contains the user session object.
 *
 * @package JAND\Common\Session
 */

namespace JAND\Common;

/**
 * A user session.
 */
class Session
{

    /**
     * User's first name.
     *
     * @var string $firstName User's first name.
     */
    private string $firstName;

    /**
     * User's last name.
     *
     * @var string $lastName User's last name.
     */
    private string $lastName;

    /**
     * This session's token.
     * Random 16 byte string.
     *
     * @var string $sessionToken Session token.
     */
    private string $sessionToken;

    /**
     * Session expiration time.
     * Unix epoch timestamp.
     *
     * @var integer $sessionExpiration Session expiry timestamp.
     */
    private int $sessionExpiration;

    /**
     * User ID.
     *
     * @var string $userId ID of user.
     */
    private string $userId;


    /**
     * Creates a new session.
     *
     * @param string  $sessionToken      Session token.
     * @param integer $sessionExpiration Session expiration.
     * @param string  $userId            ID of user session is for.
     * @param string  $firstName         User's first name.
     * @param string  $lastName          User's last name.
     */
    public function __construct(
        string $sessionToken,
        int $sessionExpiration,
        string $userId,
        string $firstName,
        string $lastName
    ) {
        $this->firstName         = $firstName;
        $this->lastName          = $lastName;
        $this->sessionToken      = $sessionToken;
        $this->sessionExpiration = $sessionExpiration;
        $this->userId            = $userId;

    }//end __construct()


    /**
     * Gets user's first name.
     *
     * @return string User first name.
     */
    public function getFirstName()
    {
        return $this->firstName;

    }//end getFirstName()


    /**
     * Gets user's last name.
     *
     * @return string User last name.
     */
    public function getLastName()
    {
        return $this->lastName;

    }//end getLastName()


    /**
     * Gets user's full name.
     *
     * @return string User full name.
     */
    public function getFullName()
    {
        return $this->firstName.' '.$this->lastName;

    }//end getFullName()


    /**
     * Gets session token.
     *
     * @return string Session token.
     */
    public function getSessionToken()
    {
        return $this->sessionToken;

    }//end getSessionToken()


    /**
     * Gets session expiration time.
     *
     * @return integer Session expiration timestamp.
     */
    public function getSessionExpiration()
    {
        return $this->sessionExpiration;

    }//end getSessionExpiration()


    /**
     * Gets the user ID.
     *
     * @return string User ID.
     */
    public function getUserId()
    {
        return $this->userId;

    }//end getUserId()


}//end class
