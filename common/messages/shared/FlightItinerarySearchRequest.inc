<?php
/**
 * Contains request for a flight itinerary.
 *
 * @package JAND\Common\Messages\Shared\FlightItinerarySearchRequest
 */

namespace JAND\Common\Messages\Shared;

/**
 * Request for a flight itinerary.
 */
class FlightItinerarySearchRequest extends \JAND\Common\Messages\Request
{

    /**
     * Trip origin.
     *
     * @var \JAND\Common\Trips\AirportCity $tripOrigin
     */
    private \JAND\Common\Trips\AirportCity $tripOrigin;

    /**
     * Trip destination.
     *
     * @var \JAND\Common\Trips\AirportCity $tripDestination
     */
    private \JAND\Common\Trips\AirportCity $tripDestination;

    /**
     * Start date of trip.
     *
     * @var \DateTime $startDate;
     */
    private \DateTime $startDate;

    /**
     * End date of trip.
     * Null if one way.
     *
     * @var ?\DateTime $endDate
     */
    private ?\DateTime $endDate;

    /**
     * Number of adult passengers.
     *
     * @var integer $adults
     */
    private int $adults;

    /**
     * Number of children passengers.
     *
     * @var integer $children
     */
    private int $children;

    /**
     * Number of lap infants.
     *
     * @var integer $infants
     */
    private int $infants;

    /**
     * Whether trip is one way.
     *
     * @var boolean $oneWay
     */
    private bool $oneWay;


    /**
     * Creates a new flight itinerary search request.
     *
     * @param \JAND\Common\Trips\AirportCity $tripOrigin      Trip origin.
     * @param \JAND\Common\Trips\AirportCity $tripDestination Trip destination.
     * @param \DateTime                      $startDate       Start date.
     * @param \DateTime                      $endDate         End date.
     * @param integer                        $adults          Number of adult pax.
     * @param integer                        $children        Number of children pax.
     * @param integer                        $infants         Number of infant pax.
     * @param boolean                        $oneWay          Whether trip is one way.
     */
    public function __construct(
        \JAND\Common\Trips\AirportCity $tripOrigin,
        \JAND\Common\Trips\AirportCity $tripDestination,
        \DateTime $startDate,
        ?\DateTime $endDate,
        int $adults,
        int $children=0,
        int $infants=0,
        bool $oneWay=false
    ) {
        $this->tripOrigin      = $tripOrigin;
        $this->tripDestination = $tripDestination;
        $this->startDate       = $startDate;
        $this->endDate         = $endDate;
        $this->adults          = $adults;
        $this->children        = $children;
        $this->infants         = $infants;
        $this->oneWay          = $oneWay;

    }//end __construct()


    /**
     * Gets trip origin.
     *
     * @return \JAND\Common\Trips\AirportCity Trip origin.
     */
    public function getOrigin()
    {
        return $this->tripOrigin;

    }//end getOrigin()


    /**
     * Gets trip destination.
     *
     * @return \JAND\Common\Trips\AirportCity Trip destination.
     */
    public function getDestination()
    {
        return $this->tripDestination;

    }//end getDestination()


        /**
         * Gets trip start date.
         *
         * @return \DateTime Trip start date.
         */
    public function getStartDate()
    {
        return $this->startDate;

    }//end getStartDate()


    /**
     * Gets trip end date.
     *
     * @return ?\DateTime Trip end date.
     */
    public function getEndDate()
    {
        return $this->endDate;

    }//end getEndDate()


    /**
     * Gets the number of adult pax.
     *
     * @return integer Adult pax.
     */
    public function getAdults()
    {
        return $this->adults;

    }//end getAdults()


    /**
     * Gets the number of children pax.
     *
     * @return integer Children pax.
     */
    public function getChildren()
    {
        return $this->children;

    }//end getChildren()


    /**
     * Gets the number of infant pax.
     *
     * @return integer Infant pax.
     */
    public function getInfants()
    {
        return $this->infants;

    }//end getInfants()


    /**
     * Gets whether trip is one way.
     *
     * @return boolean Whether trip is one way.
     */
    public function getOneWay()
    {
        return $this->oneWay;

    }//end getOneWay()


}//end class
