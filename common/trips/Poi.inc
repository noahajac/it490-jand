<?php
/**
 * Contains class for a poi.
 *
 * @package JAND\Common\Trips\Poi
 */

namespace JAND\Common\Trips;

/**
 * A point of interest.
 */
class Poi
{

    /**
     * Unique poi ID.
     * May be null if coming from DMZ.
     *
     * @var integer Poi ID.
     */
    private ?int $poiId;

    /**
     * City poi is in.
     *
     * @var AirportCity $city City poi is in.
     */
    private ?AirportCity $city;

    /**
     * Poi keyword tags.
     *
     * @var string[] $tags Keyword tags.
     */
    private array $tags;

    /**
     * Name of poi.
     *
     * @var string $name Name of poi.
     */
    private ?string $name;


    /**
     * Creates a new poi.
     *
     * @param integer     $poiId Unique poi ID.
     * @param AirportCity $city  City of poi.
     * @param string[]    $tags  Keyword tags.
     * @param string      $name  Name of poi.
     */
    public function __construct(
        ?int $poiId,
        ?AirportCity $city,
        array $tags,
        ?string $name
    ) {
        $this->poiId = $poiId;
        $this->city  = $city;
        $this->tags  = $tags;
        $this->name  = $name;

    }//end __construct()


    /**
     * Gets the poi ID.
     *
     * @return integer Poi ID.
     */
    public function getPoiId()
    {
        return $this->poiId;

    }//end getPoiId()


    /**
     * Gets poi city.
     *
     * @return ?AirportCity Poi city.
     */
    public function getCity()
    {
        return $this->city;

    }//end getCity()


    /**
     * Gets tags.
     *
     * @return string[] Keyword tags.
     */
    public function getTags()
    {
        return $this->tags;

    }//end getTags()


    /**
     * Gets poi name.
     *
     * @return ?string Poi name.
     */
    public function getName()
    {
        return $this->name;

    }//end getName()


}//end class
