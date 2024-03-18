<?php
/**
 * A generic review.
 *
 * @package JAND\Common\Trips\Review
 */

namespace JAND\Common\Trips;


/**
 * A review.
 */
abstract class Review
{

    /**
     * Review ID.
     * Null if new.
     *
     * @var ?int $reviewId Review ID.
     */
    private ?int $reviewId;

    /**
     * Rating from 1 to 5.
     *
     * @var integer $rating Rating from 1 to 5.
     */
    private int $rating;

    /**
     * User's comment.
     *
     * @var string $comment User's comment.
     */
    private string $comment;


    /**
     * Creates a new review.
     *
     * @param integer $reviewId Review ID.
     * @param integer $rating   Rating from 1 to 5.
     * @param string  $comment  User comment.
     */
    protected function __construct(?int $reviewId=null, int $rating, string $comment)
    {
        $this->reviewId = $reviewId;
        $this->rating   = $rating;
        $this->comment  = $comment;

    }//end __construct()


    /**
     * Gets review ID.
     *
     * @return ?int Review ID.
     */
    public function getReviewId()
    {
        return $this->reviewId;

    }//end getReviewId()


    /**
     * Gets rating.
     *
     * @return integer Rating from 1 to 5.
     */
    public function getRating()
    {
        return $this->rating;

    }//end getRating()


    /**
     * Gets comment.
     *
     * @return string User comment.
     */
    public function getComment()
    {
        return $this->comment;

    }//end getComment()


}//end class
