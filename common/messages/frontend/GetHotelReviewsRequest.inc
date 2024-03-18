<?php
/**
 * Request to get hotel reviews.
 *
 * @package JAND\Common\Messages\Frontend\GetHotelReviewsRequest
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Request to get hotel reviews.
 */
class GetHotelReviewsRequest extends SessionRequest
{

    /**
     * The hotel.
     *
     * @var \JAND\Common\Trips\Hotel $hotel The hotel.
     */
    private \JAND\Common\Trips\Hotel $hotel;


    /**
     * Creates a new get review request.
     *
     * @param string                   $sessionToken Session token.
     * @param \JAND\Common\Trips\Hotel $hotel        The hotel.
     */
    public function __construct(string $sessionToken, \JAND\Common\Trips\Hotel $hotel)
    {
        parent::__construct($sessionToken);
        $this->hotel = $hotel;

    }//end __construct()


    /**
     * Gets the hotel.
     *
     * @return \JAND\Common\Trips\Hotel The hotel.
     */
    public function getHotel()
    {
        return $this->hotel;

    }//end getHotel()


}//end class
