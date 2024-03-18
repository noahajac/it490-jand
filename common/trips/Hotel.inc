<?php
/**
 * Contains class for a hotel.
 *
 * @package JAND\Common\Trips\Hotel
 */

namespace JAND\Common\Trips;

/**
 * A hotel.
 */
class Hotel
{

    /**
     * Unique hotel ID.
     * May be null if coming from DMZ.
     *
     * @var integer Hotel ID.
     */
    private ?int $hotelId;

    /**
     * City hotel is in.
     *
     * @var AirportCity $city City hotel is in.
     */
    private ?AirportCity $city;

    /**
     * Hotel code.
     *
     * @var string $hotelCode Amadeus hotel code.
     */
    private ?string $hotelCode;

    /**
     * Name of hotel.
     *
     * @var string $name Name of hotel.
     */
    private ?string $name;


    /**
     * Creates a new hotel.
     *
     * @param integer     $hotelId   Unique hotel ID.
     * @param AirportCity $city      City of hotel.
     * @param string      $hotelCode Amadeus code.
     * @param string      $name      Name of hotel.
     */
    public function __construct(
        ?int $hotelId,
        ?AirportCity $city,
        ?string $hotelCode,
        ?string $name
    ) {
        $this->hotelId   = $hotelId;
        $this->city      = $city;
        $this->hotelCode = $hotelCode;
        $this->name      = $name;

    }//end __construct()


    /**
     * Gets the hotel ID.
     *
     * @return ?integer Hotel ID.
     */
    public function getHotelId()
    {
        return $this->hotelId;

    }//end getHotelId()


    /**
     * Gets hotel city.
     *
     * @return ?AirportCity Hotel city.
     */
    public function getCity()
    {
        return $this->city;

    }//end getCity()


    /**
     * Gets hotel code.
     *
     * @return ?string Hotel code.
     */
    public function getHotelCode()
    {
        return $this->hotelCode;

    }//end getHotelCode()


    /**
     * Gets hotel name.
     *
     * @return ?string Hotel name.
     */
    public function getName()
    {
        return $this->name;

    }//end getName()


}//end class
