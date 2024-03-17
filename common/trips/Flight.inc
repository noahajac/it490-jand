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
     * Unique flight ID.
     * May be null if coming from DMZ.
     *
     * @var integer Flight ID.
     */
    private ?int $flightId;

    /**
     * Departure airport.
     *
     * @var AirportCity $departAirport Departure airport.
     */
    private AirportCity $departAirport;

    /**
     * Arrival airport.
     *
     * @var AirportCity $arrivalAirport Arrival airport.
     */
    private AirportCity $arrivalAirport;

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
     * Name of cabin class.
     *
     * @var string $className
     */
    private string $className;


    /**
     * Creates a new flight.
     *
     * @param integer     $flightId       Unique flight ID.
     * @param AirportCity $departAirport  Departure airport.
     * @param AirportCity $arrivalAirport Arrival airport.
     * @param \DateTime   $departTime     Departure time.
     * @param \DateTime   $arrivalTime    Arrival time.
     * @param Airline     $airline        Airline.
     * @param integer     $flightNo       Flight number.
     * @param string      $className      Name of cabin class.
     */
    public function __construct(
        ?int $flightId,
        AirportCity $departAirport,
        AirportCity $arrivalAirport,
        \DateTime $departTime,
        \DateTime $arrivalTime,
        Airline $airline,
        int $flightNo,
        string $className
    ) {
        $this->flightId       = $flightId;
        $this->departAirport  = $departAirport;
        $this->arrivalAirport = $arrivalAirport;
        $this->departTime     = $departTime;
        $this->arrivalTime    = $arrivalTime;
        $this->airline        = $airline;
        $this->flightNo       = $flightNo;
        $this->className      = $className;

    }//end __construct()


    /**
     * Gets the flight ID.
     *
     * @return integer Flight ID.
     */
    public function getFlightId()
    {
        return $this->flightId;

    }//end getFlightId()


    /**
     * Gets departure airport.
     *
     * @return AirportCity Departure airport.
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


    /**
     * Gets class name.
     *
     * @return string Cabin class name
     */
    public function getClassName()
    {
        return $this->className;

    }//end getClassName()


}//end class
