<?php
/**
 * Response that gives all user bookings.
 *
 * @package JAND\Common\Messages\Frontend\GetBookingsResponse
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Response with all user bookings.
 */
class GetBookingsResponse
{

    /**
     * Array of user's flight bookings.
     *
     * @var \JAND\Common\Trips\FlightItinerary[] $flights Array of flight bookings.
     */
    private array $flights;

    /**
     * Array of user's hotel bookings.
     *
     * @var \JAND\Common\Trips\HotelItinerary[] $hotels Array of hotel bookings.
     */
    private array $hotels;


    /**
     * Creates a get booking response.
     *
     * @param \JAND\Common\Trips\FlightItinerary[] $flights Array of flights.
     * @param \JAND\Common\Trips\HotelItinerary[]  $hotels  Array of hotels.
     */
    public function __construct(array $flights, array $hotels)
    {
        $this->flights = $flights;
        $this->hotels  = $hotels;

    }//end __construct()


    /**
     * Gets flights.
     *
     * @return \JAND\Common\Trips\FlightItinerary[] Array of flights.
     */
    public function getFlights()
    {
        return $this->flights;

    }//end getFlights()


    /**
     * Gets hotels.
     *
     * @return \JAND\Common\Trips\HotelItinerary[] Array of hotels.
     */
    public function getHotels()
    {
        return $this->hotels;

    }//end getHotels()


}//end class
