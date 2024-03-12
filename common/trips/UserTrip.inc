<?php
/**
 * A user's trip.
 *
 * @package JAND\Common\Trips\UserTrip
 */

namespace JAND\Common\Trips;

/**
 * A user's trip.
 */
class UserTrip
{

    /**
     * Unique trip ID.
     *
     * May not be set for new trips from frontend.
     *
     * @var integer $tripId Unique trip ID.
     */
    private ?int $tripId;

    /**
     * Trip destination.
     *
     * @var string $tripDestination Trip destination.
     */
    private AirportCity $tripDestination;

    /**
     * Trip start date.
     *
     * @var \DateTime $startDate Trip start date.
     */
    private \DateTime $startDate;

    /**
     * Trip end date.
     *
     * @var \DateTime $endDate Trip end date.
     */
    private \DateTime $endDate;


    /**
     * Creates a new user trip.
     *
     * @param integer     $tripId          Unique trip ID.
     * @param AirportCity $tripDestination Trip destination.
     * @param \DateTime   $startDate       Trip start date.
     * @param \DateTime   $endDate         Trip end date.
     */
    public function __construct(
        ?int $tripId=null,
        AirportCity $tripDestination,
        \DateTime $startDate,
        \DateTime $endDate
    ) {
        $this->tripId          = $tripId;
        $this->tripDestination = $tripDestination;
        $this->startDate       = $startDate;
        $this->endDate         = $endDate;

    }//end __construct()


    /**
     * Gets trip ID.
     *
     * @return integer Unique trip ID.
     */
    public function getTripId()
    {
        return $this->tripId;

    }//end getTripId()


    /**
     * Gets trip destination.
     *
     * @return AirportCity Trip destination.
     */
    public function getTripDestination()
    {
        return $this->tripDestination;

    }//end getTripDestination()


    /**
     * Gets trip start date.
     *
     * @return \DateTime Trip start date.
     */
    public function getTripStart()
    {
        return $this->startDate;

    }//end getTripStart()


    /**
     * Gets trip end date.
     *
     * @return \DateTime Trip end date.
     */
    public function getTripEnd()
    {
        return $this->endDate;

    }//end getTripEnd()


}//end class
