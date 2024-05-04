<?php
/**
 * Hides a POI recommendation.
 *
 * @package JAND\Common\Messages\Frontend\HideRecommendationRequest
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Hides a POI recommendation.
 */
class HideRecommendationRequest extends SessionRequest
{

    /**
     * POI id to hide.
     *
     * @var integer $poiId POI to hide.
     */
    private int $poiId;


    /**
     * Creates a hide POI request.
     *
     * @param string  $sessionId Session ID.
     * @param integer $poiId     The POI to hide.
     */
    public function __construct(string $sessionId, int $poiId)
    {
        parent::__construct($sessionId);
        $this->poiId = $poiId;

    }//end __construct()


    /**
     * Gets the POI ID to hide.
     *
     * @return integer POI to hide.
     */
    public function getPoiId()
    {
        return $this->poiId;

    }//end getPoiId()


}//end class
