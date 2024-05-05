<?php
/**
 * Contains getSegmentInfo helper for a flight.
 *
 * @package JAND\DbConnector\Includes\GetSegmentInfo
 */

namespace JAND\DbConnector\Includes;

use JAND\Common\Messages\DbConnector\AirlineSearchRequest;
use JAND\Common\Messages\Shared\AirportCitySearchRequest;
use JAND\Common\Trips\Flight;

/**
 * Contains flight get segment function.
 */
abstract class GetSegmentInfo
{


    /**
     * Takes a flight and gets airport and airline info.
     *
     * @param Flight $segment Flight from DMZ.
     * @param \PDO   $pdo     PDO for DB access.
     *
     * @return Flight Flight with all information filled.
     */
    public static function get(Flight $segment, \PDO $pdo)
    {
        $departAirport  = Responders\AirportCitySearchResponder::respondToRequest(
            new AirportCitySearchRequest(
                $segment->getDepartAirport()->getCode(),
            ),
            $pdo
        )->getResults()[0];
        $arrivalAirport = Responders\AirportCitySearchResponder::respondToRequest(
            new AirportCitySearchRequest(
                $segment->getArrivalAirport()->getCode(),
            ),
            $pdo
        )->getResults()[0];
        $airline        = Responders\AirlineSearchResponder::respondToRequest(
            new AirlineSearchRequest(
                $segment->getAirline()->getCode(),
            ),
            $pdo
        )->getResults()[0];

        return new Flight(
            $segment->getFlightId(),
            $departAirport,
            $arrivalAirport,
            $segment->getDepartTime(),
            $segment->getArrivalTime(),
            $airline,
            $segment->getFlightNo(),
            $segment->getClassName()
        );

    }//end get()


}//end class
