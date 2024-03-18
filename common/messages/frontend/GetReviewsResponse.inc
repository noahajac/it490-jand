<?php
/**
 * Response to a request for reviews.
 *
 * @package JAND\Common\Messages\Frontend\GetReviewsResponse
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Response when getting reviews.
 */
class GetReviewsResponse
{

    /**
     * Array of reviews.
     *
     * @var HotelReview[]|AirlineReview[]|PoiReview[] $review Reviews.
     */
    private array $reviews;

    /**
     * Requesting user's review.
     *
     * @var ?HotelReview|AirlineReview|PoiReview $own Review of requesting user.
     */
    private mixed $own;


    /**
     * Create a new get reviews response.
     *
     * @param HotelReview[]|AirlineReview[]|PoiReview[] $reviews Array of reviews.
     * @param HotelReview|AirlineReview|PoiReview       $own     User's own review.
     */
    public function __construct(
        array $reviews,
        mixed $own
    ) {
        $this->reviews = $reviews;
        $this->own     = $own;

    }//end __construct()


    /**
     * Get the reviews.
     *
     * @return HotelReview[]|AirlineReview[]|PoiReview[] Reviews.
     */
    public function getReviews()
    {
        return $this->reviews;

    }//end getReviews()


    /**
     * Get review of requestor.
     *
     * @return ?HotelReview|AirlineReview|PoiReview Own review.
     */
    public function getOwn()
    {
        return $this->own;

    }//end getOwn()


}//end class
