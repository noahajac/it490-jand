<?php
/**
 * A POI review.
 *
 * @package JAND\Common\Trips\PoiReview
 */

namespace JAND\Common\Trips;

/**
 * A POI review.
 */
class PoiReview extends Review
{

    /**
     * Subject of review.
     *
     * @var Poi $subject Poi.
     */
    private Poi $subject;


    /**
     * Creates an POI review.
     *
     * @param integer $reviewId Review ID.
     * @param integer $rating   Rating between 1 and 5.
     * @param string  $comment  User comment.
     * @param Poi     $poi      The POI.
     */
    public function __construct(?int $reviewId=null, int $rating, string $comment, Poi $poi)
    {
        parent::__construct($reviewId, $rating, $comment);
        $this->subject = $poi;

    }//end __construct()


    /**
     * Gets the POI.
     *
     * @return Poi The POI.
     */
    public function getPoi()
    {
        return $this->subject;

    }//end getPoi()


}//end class
