<?php
/**
 * A user review.
 *
 * @package JAND\Common\Review.inc
 */

namespace JAND\Common;

/**
 * A user review.
 */
class Review
{

    /**
     * Rating from 0 to 4.
     *
     * @var integer $rating Rating from 0 to 4.
     */
    private int $rating;

    /**
     * Actual review.
     *
     * @var string $review Review.
     */
    private string $review;

    /**
     * User ID of author.
     *
     * @var string $authorId User ID of author.
     */
    private string $authorId;


    /**
     * Creates a user review.
     *
     * @param integer $rating   Rating from 0 to 4.
     * @param string  $review   Written review.
     * @param string  $authorId Author user ID.
     */
    public function __construct(int $rating, string $review, string $authorId)
    {
        $this->rating   = $rating;
        $this->review   = $review;
        $this->authorId = $authorId;

    }//end __construct()


    /**
     * Gets the rating.
     *
     * @return integer The rating from 0 to 4.
     */
    public function getRating()
    {
        return $this->rating;

    }//end getRating()


    /**
     * Gets the review.
     *
     * @return string The review.
     */
    public function getReview()
    {
        return $this->review;

    }//end getReview()


    /**
     * Gets the author Id.
     *
     * @return string The author Id.
     */
    public function getAuthorId()
    {
        return $this->authorId;

    }//end getAuthorId()


}//end class
