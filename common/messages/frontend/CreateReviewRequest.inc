<?php
/**
 * Request to create a review.
 *
 * @package JAND\Common\Messages\Frontend\CreateReviewRequest
 */

namespace JAND\Common\Messages\Frontend;

use JAND\Common\Messages\Frontend\SessionRequest;
use JAND\Common\Trips\AirlineReview;
use JAND\Common\Trips\HotelReview;
use JAND\Common\Trips\PoiReview;

/**
 * Request to create a review.
 */
class CreateReviewRequest extends SessionRequest
{

    /**
     * The review.
     *
     * @var HotelReview|AirlineReview|PoiReview $review The review.
     */
    private HotelReview|AirlineReview|PoiReview $review;


    /**
     * Creates a review request.
     *
     * @param string                              $sessionToken Session token.
     * @param HotelReview|AirlineReview|PoiReview $review       The review.
     */
    public function __construct(string $sessionToken, HotelReview|AirlineReview|PoiReview $review)
    {
        parent::__construct($sessionToken);
        $this->review = $review;

    }//end __construct()


    /**
     * Gets review.
     *
     * @return HotelReview|AirlineReview|PoiReview Review.
     */
    public function getReview()
    {
        return $this->review;

    }//end getReview()


}//end class
