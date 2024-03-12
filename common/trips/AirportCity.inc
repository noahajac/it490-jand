<?php
/**
 * Contains class for an airport or city.
 *
 * @package JAND\Common\Trips\AirportCity
 */

namespace JAND\Common\Trips;

/**
 * An airport or city.
 */
class AirportCity extends IATACode
{

    /**
     * Latitude.
     *
     * @var float Latitude.
     */
    private float $latitude;

    /**
     * Longitude.
     *
     * @var float Longitude.
     */
    private float $longitude;

    /**
     * State code.
     *
     * @var string State code.
     */
    private string $stateCode;

    /**
     * Country code.
     *
     * @var string Country code.
     */
    private string $countryCode;


    /**
     * Creates a new airport/city object.
     *
     * @param string $code        IATA code.
     * @param string $name        Name.
     * @param float  $latitude    Latitude.
     * @param float  $longitude   Longitude.
     * @param string $stateCode   State code.
     * @param string $countryCode Country code.
     */
    public function __construct(
        string $code,
        string $name,
        float $latitude,
        float $longitude,
        string $stateCode,
        string $countryCode
    ) {
        parent::__construct($code, $name);
        $this->latitude    = $latitude;
        $this->longitude   = $longitude;
        $this->stateCode   = $stateCode;
        $this->countryCode = $countryCode;

    }//end __construct()


    /**
     * Gets latitude.
     *
     * @return float Latitude.
     */
    public function getLatitude()
    {
        return $this->latitude;

    }//end getLatitude()


    /**
     * Gets longitude.
     *
     * @return float Longitude.
     */
    public function getLongitude()
    {
        return $this->longitude;

    }//end getLongitude()


    /**
     * Gets state code.
     *
     * @return string State code.
     */
    public function getStateCode()
    {
        return $this->stateCode;

    }//end getStateCode()


    /**
     * Gets country code.
     *
     * @return string Country code.
     */
    public function getCountryCode()
    {
        return $this->countryCode;

    }//end getCountryCode()


}//end class
