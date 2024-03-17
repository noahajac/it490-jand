<?php
/**
 * Contains flight itineary search response.
 *
 * @package JAND\Common\Messages\Shared\FlightItinerarySearchResponse
 */

namespace JAND\Common\Messages\Shared;

/**
 * A flight itinerary search response.
 */
class FlightItinerarySearchResponse
{

    /**
     * Array of flight itinearies.
     *
     * @var \JAND\Common\Trips\FlightItinerary[] $flightItineraries Array of flight itineraries.
     */
    private array $flightItineraries;


    /**
     * Creates a new flight itinerary search response.
     *
     * @param \JAND\Common\Trips\FlightItinerary[] $flightItineraries Array of flight itineraries.
     */
    public function __construct(array $flightItineraries)
    {
        $this->flightItineraries = $flightItineraries;

    }//end __construct()


    /**
     * Gets flight itineraries.
     *
     * @return \JAND\Common\Trips\FlightItinerary[] Array of flight itineraries.
     */
    public function getFlightItineraries()
    {
        return $this->flightItineraries;

    }//end getFlightItineraries()


}//end class
