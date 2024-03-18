<?php
/**
 * Request to get airline reviews.
 *
 * @package JAND\Common\Messages\Frontend\GetAirlineReviewsRequest
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Request to get airline reviews.
 */
class GetAirlineReviewsRequest extends SessionRequest
{

    /**
     * The airline.
     *
     * @var \JAND\Common\Trips\Airline $airline The airline.
     */
    private \JAND\Common\Trips\Airline $airline;


    /**
     * Creates a new get review request.
     *
     * @param string                     $sessionToken Session token.
     * @param \JAND\Common\Trips\Airline $airline      The airline.
     */
    public function __construct(string $sessionToken, \JAND\Common\Trips\Airline $airline)
    {
        parent::__construct($sessionToken);
        $this->airline = $airline;

    }//end __construct()


    /**
     * Gets the airline.
     *
     * @return \JAND\Common\Trips\Airline The airline.
     */
    public function getAirline()
    {
        return $this->airline;

    }//end getAirline()


}//end class
