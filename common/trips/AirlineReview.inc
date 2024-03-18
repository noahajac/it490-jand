<?php
/**
 * An airline review.
 *
 * @package JAND\Common\Trips\AirlineReview
 */

namespace JAND\Common\Trips;

/**
 * An airline review.
 */
class AirlineReview extends Review
{

    /**
     * Subject of review.
     *
     * @var Airline $subject Airline.
     */
    private Airline $subject;


    /**
     * Creates an airline review.
     *
     * @param integer $reviewId Review ID.
     * @param integer $rating   Rating between 1 and 5.
     * @param string  $comment  User comment.
     * @param Airline $airline  The airline.
     */
    public function __construct(?int $reviewId=null, int $rating, string $comment, Airline $airline)
    {
        parent::__construct($reviewId, $rating, $comment);
        $this->subject = $airline;

    }//end __construct()


    /**
     * Gets the airline.
     *
     * @return Airline The airline.
     */
    public function getAirline()
    {
        return $this->subject;

    }//end getAirline()


}//end class
