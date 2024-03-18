<?php
/**
 * Request to get POI reviews.
 *
 * @package JAND\Common\Messages\Frontend\GetPoiReviewsRequest
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Request to get POI reviews.
 */
class GetPoiReviewsRequest extends SessionRequest
{

    /**
     * The POI.
     *
     * @var \JAND\Common\Trips\Poi $poi The POI.
     */
    private \JAND\Common\Trips\Poi $poi;


    /**
     * Creates a new get review request.
     *
     * @param string                 $sessionToken Session token.
     * @param \JAND\Common\Trips\Poi $poi          The POI.
     */
    public function __construct(string $sessionToken, \JAND\Common\Trips\Poi $poi)
    {
        parent::__construct($sessionToken);
        $this->poi = $poi;

    }//end __construct()


    /**
     * Gets the POI.
     *
     * @return \JAND\Common\Trips\Poi The POI.
     */
    public function getPoi()
    {
        return $this->poi;

    }//end getPoi()


}//end class
