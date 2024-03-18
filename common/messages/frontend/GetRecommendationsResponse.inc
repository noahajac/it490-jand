<?php
/**
 * Contains POI reccomendations response.
 *
 * @package JAND\Common\Messages\Frontend\GetRecommendationsResponse
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Response with user recommendations.
 */
class GetRecommendationsResponse
{

    /**
     * Array of POIs.
     *
     * @var \JAND\Common\Trips\Poi[] $pois Array of POIs.
     */
    private array $pois;


    /**
     * Creates a new POI search response.
     *
     * @param \JAND\Common\Trips\Poi[] $pois Array of POIs.
     */
    public function __construct(array $pois)
    {
        $this->pois = $pois;

    }//end __construct()


    /**
     * Gets POIs.
     *
     * @return \JAND\Common\Trips\Poi[] Array of POIs.
     */
    public function getPois()
    {
        return $this->pois;

    }//end getPois()


}//end class
