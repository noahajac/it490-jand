<?php
/**
 * Request to create a booking.
 *
 * @package JAND\Common\Messages\Frontend\CreateBookingRequest
 */

namespace JAND\Common\Messages\Frontend;

use JAND\Common\Messages\Frontend\SessionRequest;
use JAND\Common\Trips\FlightItinerary;
use JAND\Common\Trips\HotelItinerary;

/**
 * Request to create a booking.
 */
class CreateBookingRequest extends SessionRequest
{

    /**
     * The booking.
     *
     * @var FlightItinerary|HotelItinerary $booking The booking.
     */
    private FlightItinerary|HotelItinerary $booking;


    /**
     * Creates a booking request.
     *
     * @param string                         $sessionToken Session token.
     * @param FlightItinerary|HotelItinerary $booking      The booking.
     */
    public function __construct(string $sessionToken, FlightItinerary|HotelItinerary $booking)
    {
        parent::__construct($sessionToken);
        $this->booking = $booking;

    }//end __construct()


    /**
     * Gets booking.
     *
     * @return FlightItinerary|HotelItinerary Booking.
     */
    public function getBooking()
    {
        return $this->booking;

    }//end getBooking()


}//end class
