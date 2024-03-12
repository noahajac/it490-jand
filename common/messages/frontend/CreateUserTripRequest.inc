<?php
/**
 * Creates or updates a trips for this user.
 *
 * @package JAND\Common\Messages\Frontend\CreateUserTripRequest
 */

namespace JAND\Common\Messages\Frontend;

use JAND\Common\Trips\UserTrip;

/**
 * Message to create or update a user trip.
 */
class CreateUserTripRequest extends SessionRequest
{

    /**
     * Trip to create or update.
     *
     * @var UserTrip $trip Trip to create/update.
     */
    private UserTrip $trip;


    /**
     * Creates a new user trip request.
     *
     * @param string   $sessionToken Session token.
     * @param UserTrip $trip         Trip to update or add. Operation depends on if trip ID is set.
     */
    public function __construct(string $sessionToken, UserTrip $trip)
    {
        parent::__construct($sessionToken);
        $this->trip = $trip;

    }//end __construct()


    /**
     * Gets trip.
     *
     * @return UserTrip Trip to update/add.
     */
    public function getUserTrip()
    {
        return $this->trip;

    }//end getUserTrip()


}//end class
