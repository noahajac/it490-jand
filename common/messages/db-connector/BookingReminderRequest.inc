<?php
/**
 * Contains request for a booking reminder email.
 *
 * @package JAND\Common\Messages\DbConnector\BookingReminderRequest
 */

namespace JAND\Common\Messages\DbConnector;

use JAND\Common\Trips\FlightItinerary;
use JAND\Common\Trips\HotelItinerary;

/**
 * A request to send a booking reminder.
 */
class BookingReminderRequest extends \JAND\Common\Messages\Request
{

    /**
     * User's email.
     *
     * @var string $email User's email.
     */
    private string $email;

    /**
     * User's Id.
     *
     * @var string $userId User's Id.
     */
    private string $userId;

    /**
     * The itinerary.
     *
     * @var FlightItinerary|HotelItinerary $itinerary Itinerary.
     */
    private FlightItinerary|HotelItinerary $itinerary;


    /**
     * Creates a booking reminder request.
     *
     * @param FlightItinerary|HotelItinerary $itinerary Itinerary.
     * @param string                         $email     User's email.
     * @param integer                        $userId    User's ID.
     */
    public function __construct(FlightItinerary|HotelItinerary $itinerary, string $email, int $userId)
    {
        $this->email     = $email;
        $this->itinerary = $itinerary;
        $this->userId    = $userId;

    }//end __construct()


    /**
     * Gets user's email.
     *
     * @return string User's email.
     */
    public function getEmail()
    {
        return $this->email;

    }//end getEmail()


    /**
     * Gets user's ID.
     *
     * @return string User's ID.
     */
    public function getUserId()
    {
        return $this->userId;

    }//end getUserId()


    /**
     * Gets the itinerary.
     *
     * @return FlightItinerary|HotelItinerary Itinerary.
     */
    public function getItinerary()
    {
        return $this->itinerary;

    }//end getItinerary()


}//end class
