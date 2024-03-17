<?php
/**
 * Contains hotel itineary search response.
 *
 * @package JAND\Common\Messages\Shared\HotelItinerarySearchResponse
 */

namespace JAND\Common\Messages\Shared;

/**
 * A hotel itinerary search response.
 */
class HotelItinerarySearchResponse
{

    /**
     * Array of hotel itinearies.
     *
     * @var \JAND\Common\Trips\HotelItinerary[] $hotelItineraries Array of hotel itineraries.
     */
    private array $hotelItineraries;


    /**
     * Creates a new hotel itinerary search response.
     *
     * @param \JAND\Common\Trips\HotelItinerary[] $hotelItineraries Array of hotel itineraries.
     */
    public function __construct(array $hotelItineraries)
    {
        $this->hotelItineraries = $hotelItineraries;

    }//end __construct()


    /**
     * Gets hotel itineraries.
     *
     * @return \JAND\Common\Trips\HotelItinerary[] Array of hotel itineraries.
     */
    public function getHotelItineraries()
    {
        return $this->hotelItineraries;

    }//end getHotelItineraries()


}//end class
