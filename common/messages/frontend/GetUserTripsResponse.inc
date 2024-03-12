<?php
/**
 * Response that gives all user trips.
 *
 * @package JAND\Common\Messages\Frontend\GetUserTripsResponse
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Response with all user trips.
 */
class GetUserTripsResponse
{

    /**
     * Array of user's trips.
     *
     * @var \JAND\Common\Trips\UserTrip[] $trips Array of trips.
     */
    private array $trips;


    /**
     * Creates a get user trips response.
     *
     * @param \JAND\Common\Trips\UserTrip[] $trips Array of trips.
     */
    public function __construct(array $trips)
    {
        $this->trips = $trips;

    }//end __construct()


    /**
     * Gets user trips.
     *
     * @return \JAND\Common\Trips\UserTrip[] Array of trips.
     */
    public function getUserTrips()
    {
        return $this->trips;

    }//end getUserTrips()


}//end class
