<?php
/**
 * Contains class for a flight.
 *
 * @package JAND\Common\Trips\Flight
 */

namespace JAND\Common\Trips;

/**
 * A flight.
 */
class Flight
{

    /**
     * Departure airport.
     *
     * @var Airport $departAirport Departure airport.
     */
    private Airport $departAirport;

    /**
     * Arrival airport.
     *
     * @var Airport $arrivalAirport Arrival airport.
     */
    private Airport $arrivalAirport;

    /**
     * Departure time.
     *
     * @var \DateTime $departTime Departure time.
     */
    private \DateTime $departTime;

    /**
     * Arrival time.
     *
     * @var \DateTime $arrivalTime Arrival time.
     */
    private \DateTime $arrivalTime;

    /**
     * Airline.
     *
     * @var Airline Airline.
     */
    private Airline $airline;

    /**
     * Flight number.
     *
     * @var integer $flightNumber Flight number.
     */
    private int $flightNo;


    /**
     * Creates a new flight.
     *
     * @param Airport   $departAirport  Departure airport.
     * @param Airport   $arrivalAirport Arrival airport.
     * @param \DateTime $departTime     Departure time.
     * @param \DateTime $arrivalTime    Arrival time.
     * @param Airline   $airline        Airline.
     * @param integer   $flightNo       Flight number.
     */
    public function __construct(
        Airport $departAirport,
        Airport $arrivalAirport,
        \DateTime $departTime,
        \DateTime $arrivalTime,
        Airline $airline,
        int $flightNo
    ) {
        $this->departAirport  = $departAirport;
        $this->arrivalAirport = $arrivalAirport;
        $this->departTime     = $departTime;
        $this->arrivalTime    = $arrivalTime;
        $this->airline        = $airline;
        $this->flightNo       = $flightNo;

    }//end __construct()


    /**
     * Gets departure airport.
     *
     * @return Airport Departure airport.
     */
    public function getDepartAirport()
    {
        return $this->departAirport;

    }//end getDepartAirport()


    /**
     * Gets arrival airport.
     *
     * @return Airport Arrival airport.
     */
    public function getArrivalAirport()
    {
        return $this->arrivalAirport;

    }//end getArrivalAirport()


    /**
     * Gets departure time.
     *
     * @return \DateTime Departure time.
     */
    public function getDepartTime()
    {
        return $this->departTime;

    }//end getDepartTime()


    /**
     * Gets arrival time.
     *
     * @return \DateTime Arrival time.
     */
    public function getArrivalTime()
    {
        return $this->arrivalTime;

    }//end getArrivalTime()


    /**
     * Gets airline.
     *
     * @return Airline Airline.
     */
    public function getAirline()
    {
        return $this->airline;

    }//end getAirline()


    /**
     * Gets flight number.
     *
     * @return integer Flight number.
     */
    public function getFlightNo()
    {
        return $this->flightNo;

    }//end getFlightNo()


}//end class
