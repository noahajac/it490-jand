<?php
/**
 * Request to create a booking.
 *
 * @package JAND\Common\Messages\Shared\CreateBookingRequest
 */

namespace JAND\Common\Messages\Shared;

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
     * User's email.
     *
     * @var ?string $email User's email.
     */
    private ?string $email;


    /**
     * Creates a booking request.
     *
     * @param string                         $sessionToken Session token.
     * @param FlightItinerary|HotelItinerary $booking      The booking.
     * @param string                         $email        The user's email.
     */
    public function __construct(string $sessionToken, FlightItinerary|HotelItinerary $booking, ?string $email=null)
    {
        parent::__construct($sessionToken);
        $this->booking = $booking;
        $this->email   = $email;

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


    /**
     * Gets user's email.
     *
     * @return string Email.
     */
    public function getEmail()
    {
        return $this->email;

    }//end getEmail()


}//end class
