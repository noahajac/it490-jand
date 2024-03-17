<?php
/**
 * Contains request for a hotel itinerary.
 *
 * @package JAND\Common\Messages\Shared\HotelItinerarySearchRequest
 */

namespace JAND\Common\Messages\Shared;

/**
 * Request for a hotel itinerary.
 */
class HotelItinerarySearchRequest extends \JAND\Common\Messages\Request
{

    /**
     * City to search for.
     *
     * @var \JAND\Common\Trips\AirportCity $city
     */
    private \JAND\Common\Trips\AirportCity $city;

    /**
     * Start date of trip.
     *
     * @var \DateTime $startDate;
     */
    private \DateTime $startDate;

    /**
     * End date of trip.
     *
     * @var \DateTime $endDate
     */
    private \DateTime $endDate;

    /**
     * Number of adults.
     *
     * @var integer $adults
     */
    private int $adults;


    /**
     * Creates a new hotel itinerary search request.
     *
     * @param \JAND\Common\Trips\AirportCity $city      Hotel city.
     * @param \DateTime                      $startDate Start date.
     * @param \DateTime                      $endDate   End date.
     * @param integer                        $adults    Number of adults.
     */
    public function __construct(
        \JAND\Common\Trips\AirportCity $city,
        \DateTime $startDate,
        \DateTime $endDate,
        int $adults,
    ) {
        $this->city      = $city;
        $this->startDate = $startDate;
        $this->endDate   = $endDate;
        $this->adults    = $adults;

    }//end __construct()


    /**
     * Gets hotel city.
     *
     * @return \JAND\Common\Trips\AirportCity Hotel city.
     */
    public function getCity()
    {
        return $this->city;

    }//end getCity()


    /**
     * Gets trip check in date.
     *
     * @return \DateTime Trip check in date.
     */
    public function getStartDate()
    {
        return $this->startDate;

    }//end getStartDate()


    /**
     * Gets trip check out date.
     *
     * @return \DateTime Trip check out date.
     */
    public function getEndDate()
    {
        return $this->endDate;

    }//end getEndDate()


    /**
     * Gets the number of adults.
     *
     * @return integer Adult guests.
     */
    public function getAdults()
    {
        return $this->adults;

    }//end getAdults()


}//end class
