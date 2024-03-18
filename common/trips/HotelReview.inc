<?php
/**
 * A hotel review.
 *
 * @package JAND\Common\Trips\HotelReview
 */

namespace JAND\Common\Trips;

/**
 * A hotel review.
 */
class HotelReview extends Review
{

    /**
     * Subject of review.
     *
     * @var Hotel $subject Hotel.
     */
    private Hotel $subject;


    /**
     * Creates an hotel review.
     *
     * @param integer $reviewId Review ID.
     * @param integer $rating   Rating between 1 and 5.
     * @param string  $comment  User comment.
     * @param Hotel   $hotel    The hotel.
     */
    public function __construct(?int $reviewId=null, int $rating, string $comment, Hotel $hotel)
    {
        parent::__construct($reviewId, $rating, $comment);
        $this->subject = $hotel;

    }//end __construct()


    /**
     * Gets the hotel.
     *
     * @return Hotel The hotel.
     */
    public function getHotel()
    {
        return $this->subject;

    }//end getHotel()


}//end class
