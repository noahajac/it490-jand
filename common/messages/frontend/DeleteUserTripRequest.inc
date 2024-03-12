<?php
/**
 * Deletes a trips for this user.
 *
 * @package JAND\Common\Messages\Frontend\DeleteUserTripRequest
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Message to delete a user trip.
 */
class DeleteUserTripRequest extends SessionRequest
{

    /**
     * Trip to delete.
     *
     * @var integer $tripId Trip to delete.
     */
    private int $tripId;


    /**
     * Creates a new user trip delete request.
     *
     * @param string  $sessionToken Session token.
     * @param integer $tripId       Trip to delete.
     */
    public function __construct(string $sessionToken, int $tripId)
    {
        parent::__construct($sessionToken);
        $this->tripId = $tripId;

    }//end __construct()


    /**
     * Gets trip ID.
     *
     * @return integer Trip to delete.
     */
    public function getTripId()
    {
        return $this->tripId;

    }//end getTripId()


}//end class
