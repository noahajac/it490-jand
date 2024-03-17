<?php
/**
 * Contains request for a POI search.
 *
 * @package JAND\Common\Messages\Shared\PoiSearchRequest
 */

namespace JAND\Common\Messages\Shared;

/**
 * Request for a POI search.
 */
class PoiSearchRequest extends \JAND\Common\Messages\Request
{

    /**
     * City to search for.
     *
     * @var \JAND\Common\Trips\AirportCity $city
     */
    private \JAND\Common\Trips\AirportCity $city;


    /**
     * Creates a new hotel itinerary search request.
     *
     * @param \JAND\Common\Trips\AirportCity $city POI city.
     */
    public function __construct(
        \JAND\Common\Trips\AirportCity $city,
    ) {
        $this->city = $city;

    }//end __construct()


    /**
     * Gets searched city.
     *
     * @return \JAND\Common\Trips\AirportCity Searched city.
     */
    public function getCity()
    {
        return $this->city;

    }//end getCity()


}//end class
