<?php
/**
 * Class representing an itinerary for a hotel.
 *
 * @package JAND\Common\Trips\HotelItinerary
 */

namespace JAND\Common\Trips;


/**
 * An itinerary for a hotel.
 */
class HotelItinerary
{

    /**
     * Unique hotel itinerary ID.
     *
     * @var ?integer Unique ID.
     */
    private ?int $itinieraryId;

    /**
     * Hotel this itinerary is for.
     *
     * @var Hotel $hotel The hotel.
     */
    private ?Hotel $hotel;

    /**
     * Start date of stay.
     *
     * @var \DateTime $startDate;
     */
    private ?\DateTime $startDate;

    /**
     * End date of stay.
     * Null if one way.
     *
     * @var ?\DateTime $endDate
     */
    private ?\DateTime $endDate;

    /**
     * Grand total of itinerary.
     *
     * @var float $grandTotal
     */
    private float $grandTotal;

    /**
     * Number of adult guests.
     *
     * @var integer $adults
     */
    private int $adults;


    /**
     * Creates a new hotel itinerary.
     *
     * @param integer   $itineraryId Unique itinerary ID.
     * @param Hotel     $hotel       The hotel.
     * @param \DateTime $startDate   Start date.
     * @param \DateTime $endDate     End date.
     * @param float     $grandTotal  Grand price total.
     * @param integer   $adults      Number of adult guests.
     */
    public function __construct(
        ?int $itineraryId=null,
        ?Hotel $hotel,
        ?\DateTime $startDate,
        ?\DateTime $endDate,
        float $grandTotal,
        int $adults,
    ) {
        $this->itinieraryId = $itineraryId;
        $this->hotel        = $hotel;
        $this->startDate    = $startDate;
        $this->endDate      = $endDate;
        $this->grandTotal   = $grandTotal;
        $this->adults       = $adults;

    }//end __construct()


    /**
     * Gets the itinerary ID.
     *
     * @return integer Itinerary ID.
     */
    public function getItineraryId()
    {
        return $this->itinieraryId;

    }//end getItineraryId()


    /**
     * Gets the hotel.
     *
     * @return Hotel The hotel.
     */
    public function getHotel()
    {
        return $this->hotel;

    }//end getHotel()


    /**
     * Gets check-in date.
     *
     * @return \DateTime Check in date.
     */
    public function getStartDate()
    {
        return $this->startDate;

    }//end getStartDate()


    /**
     * Gets check out date.
     *
     * @return \DateTime Check out date.
     */
    public function getEndDate()
    {
        return $this->endDate;

    }//end getEndDate()


    /**
     * Gets the grand total price.
     *
     * @return float Grand total.
     */
    public function getGrandTotal()
    {
        return $this->grandTotal;

    }//end getGrandTotal()


    /**
     * Gets the number of adult guests.
     *
     * @return integer Adult guests.
     */
    public function getAdults()
    {
        return $this->adults;

    }//end getAdults()


}//end class
