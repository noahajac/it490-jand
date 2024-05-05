<?php
/**
 * Contains request for a price alert email.
 *
 * @package JAND\Common\Messages\DbConnector\PriceAlertRequest
 */

namespace JAND\Common\Messages\DbConnector;

use JAND\Common\Trips\FlightItinerary;

/**
 * A request to send a booking reminder.
 */
class PriceAlertRequest extends \JAND\Common\Messages\Request
{

    /**
     * User's email.
     *
     * @var string $email User's email.
     */
    private string $email;

    /**
     * The itinerary.
     *
     * @var FlightItinerary $itinerary Itinerary.
     */
    private FlightItinerary $itinerary;


    /**
     * Creates a price alert request.
     *
     * @param FlightItinerary $itinerary Itinerary.
     * @param string          $email     User's email.
     */
    public function __construct(FlightItinerary $itinerary, string $email)
    {
        $this->email     = $email;
        $this->itinerary = $itinerary;

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
     * Gets the itinerary.
     *
     * @return FlightItinerary Itinerary.
     */
    public function getItinerary()
    {
        return $this->itinerary;

    }//end getItinerary()


}//end class
