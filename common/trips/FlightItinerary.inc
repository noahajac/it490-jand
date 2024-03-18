<?php
/**
 * Class representing an itinerary of flights.
 *
 * @package JAND\Common\Trips\FlightItinerary
 */

namespace JAND\Common\Trips;


/**
 * An itinerary of flights.
 */
class FlightItinerary
{

    /**
     * Unique flight itinerary ID.
     *
     * @var ?integer Unique ID.
     */
    private ?int $itinieraryId;

    /**
     * Array of outbound flight segments.
     * In order from first to last.
     *
     * @var Flight[] $outboundSegments
     */
    private array $outboundSegments;

    /**
     * Array of return flight segments.
     * In order from first to last.
     * Null if one way.
     *
     * @var Flight[] $returnSegments
     */
    private ?array $returnSegments;

    /**
     * Trip origin.
     *
     * @var AirportCity $tripOrigin
     */
    private ?AirportCity $tripOrigin;

    /**
     * Trip destination.
     *
     * @var AirportCity $tripDestination
     */
    private ?AirportCity $tripDestination;

    /**
     * Start date of trip.
     *
     * @var \DateTime $startDate;
     */
    private ?\DateTime $startDate;

    /**
     * End date of trip.
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
     * Creates a new flight itinerary.
     *
     * @param integer     $itineraryId      Unique itinerary ID.
     * @param Flight[]    $outboundSegments Outbound flight segments.
     * @param Flight[]    $returnSegments   Return flight segments.
     * @param AirportCity $tripOrigin       Trip origin.
     * @param AirportCity $tripDestination  Trip destination.
     * @param \DateTime   $startDate        Start date.
     * @param \DateTime   $endDate          End date.
     * @param float       $grandTotal       Grand price total.
     * @param integer     $adults           Number of adult pax.
     * @param integer     $children         Number of children pax.
     * @param integer     $infants          Number of infant pax.
     * @param boolean     $oneWay           Whether trip is one way.
     */
    public function __construct(
        ?int $itineraryId=null,
        array $outboundSegments,
        ?array $returnSegments,
        ?AirportCity $tripOrigin,
        ?AirportCity $tripDestination,
        ?\DateTime $startDate,
        ?\DateTime $endDate,
        float $grandTotal,
        int $adults,
        int $children=0,
        int $infants=0,
        bool $oneWay=false
    ) {
        $this->itinieraryId     = $itineraryId;
        $this->outboundSegments = $outboundSegments;
        $this->returnSegments   = $returnSegments;
        $this->tripOrigin       = $tripOrigin;
        $this->tripDestination  = $tripDestination;
        $this->startDate        = $startDate;
        $this->endDate          = $endDate;
        $this->grandTotal       = $grandTotal;
        $this->adults           = $adults;
        $this->children         = $children;
        $this->infants          = $infants;
        $this->oneWay           = $oneWay;

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
     * Gets the outbound flight segments.
     *
     * @return Flight[] Flight segments
     */
    public function getOutboundSegments()
    {
        return $this->outboundSegments;

    }//end getOutboundSegments()


    /**
     * Gets the return flight segments.
     *
     * @return Flight[] Flight segments
     */
    public function getReturnSegments()
    {
        return $this->returnSegments;

    }//end getReturnSegments()


    /**
     * Gets trip origin.
     *
     * @return AirportCity Trip origin.
     */
    public function getOrigin()
    {
        return $this->tripOrigin;

    }//end getOrigin()


    /**
     * Gets trip destination.
     *
     * @return AirportCity Trip destination.
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
     * Gets the grand total price.
     *
     * @return float Grand total.
     */
    public function getGrandTotal()
    {
        return $this->grandTotal;

    }//end getGrandTotal()


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
