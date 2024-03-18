<?php
/**
 * Contains the responder for a get bookings request.
 *
 * @package JAND\DbConnector\Includes\Responders\GetBookingsResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use JAND\Common\Messages\DbConnector\AirlineSearchRequest;
use JAND\Common\Messages\Shared\AirportCitySearchRequest;
use JAND\Common\Trips\Airline;
use JAND\Common\Trips\AirportCity;
use JAND\Common\Trips\Flight;
use JAND\Common\Trips\Hotel;

/**
 * Responds to get booking requests.
 */
abstract class GetBookingsResponder
{


    /**
     * Takes a flight and gets airport and airline info.
     *
     * @param Flight $segment Flight from DMZ.
     * @param \PDO   $pdo     PDO for DB access.
     *
     * @return Flight Flight with all information filled.
     */
    private static function getSegmentInfo(Flight $segment, \PDO $pdo)
    {
        $departAirport  = AirportCitySearchResponder::respondToRequest(
            new AirportCitySearchRequest(
                $segment->getDepartAirport()->getCode(),
            ),
            $pdo
        )->getResults()[0];
        $arrivalAirport = AirportCitySearchResponder::respondToRequest(
            new AirportCitySearchRequest(
                $segment->getArrivalAirport()->getCode(),
            ),
            $pdo
        )->getResults()[0];
        $airline        = AirlineSearchResponder::respondToRequest(
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

    }//end getSegmentInfo()


    /**
     * Responds to a get user trips request.
     *
     * @param \JAND\Common\Messages\Frontend\GetBookingsRequest $request Get request.
     * @param \PDO                                              $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\GetBookingsResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Frontend\GetBookingsRequest $request, \PDO $pdo)
    {
        $sessionToken = $request->getSessionToken();

        $flights = [];
        $hotels  = [];

        $flightItinerarySelectStmt = $pdo->prepare(
            'SELECT f.* FROM flight_itineraries f, flight_bookings b, sessions s WHERE 
f.itinerary_id=b.itinerary_id AND s.session_token=:sessionToken AND s.user_id=b.user_id'
        );
        $flightItinerarySelectStmt->execute(
            ['sessionToken' => $sessionToken]
        );
        $flightItinerarySelectResults = $flightItinerarySelectStmt->fetchAll();
        $flightItinerarySelectStmt->closeCursor();

        foreach ($flightItinerarySelectResults as &$itinerary) {
            $outboundSegmentSelectQuery = $pdo->prepare(
                'SELECT * FROM 
itinerary_out_segments s, flights f WHERE itinerary_id=:itineraryId 
AND f.flight_id=s.flight_id ORDER BY s.position'
            );
            $outboundSegmentSelectQuery->execute(
                [
                    'itineraryId' => $itinerary['itinerary_id'],
                ]
            );
            $outboundSegmentSelectResults = $outboundSegmentSelectQuery->fetchAll();
            $outboundSegmentSelectQuery->closeCursor();

            $outboundSegments = [];
            foreach ($outboundSegmentSelectResults as &$segment) {
                array_push(
                    $outboundSegments,
                    static::getSegmentInfo(
                        new Flight(
                            $segment['flight_id'],
                            new AirportCity($segment['depart_airport'], null, null, null, null),
                            new AirportCity($segment['arrival_airport'], null, null, null, null),
                            new \DateTime($segment['depart_time']),
                            new \DateTime($segment['arrival_time']),
                            new Airline($segment['airline'], null),
                            $segment['flight_no'],
                            $segment['class_name']
                        ),
                        $pdo
                    )
                );
            }//end foreach

            $returnSegments = null;
            if (!(bool) $itinerary['one_way']) {
                $returnSegmentSelectQuery = $pdo->prepare(
                    'SELECT * FROM 
itinerary_return_segments s, flights f WHERE itinerary_id=:itineraryId 
AND f.flight_id=s.flight_id ORDER BY s.position'
                );
                $returnSegmentSelectQuery->execute(
                    [
                        'itineraryId' => $itinerary['itinerary_id'],
                    ]
                );
                $returnSegmentSelectResults = $returnSegmentSelectQuery->fetchAll();
                $returnSegmentSelectQuery->closeCursor();

                $returnSegments = [];
                foreach ($returnSegmentSelectResults as &$segment) {
                    array_push(
                        $returnSegments,
                        static::getSegmentInfo(
                            new Flight(
                                $segment['flight_id'],
                                new AirportCity($segment['depart_airport'], null, null, null, null, null),
                                new AirportCity($segment['arrival_airport'], null, null, null, null, null),
                                new \DateTime($segment['depart_time']),
                                new \DateTime($segment['arrival_time']),
                                new Airline($segment['airline'], null),
                                $segment['flight_no'],
                                $segment['class_name']
                            ),
                            $pdo
                        )
                    );
                }//end foreach
            }//end if

            $origin      = AirportCitySearchResponder::respondToRequest(
                new AirportCitySearchRequest(
                    $itinerary['origin'],
                ),
                $pdo
            )->getResults()[0];
            $destination = AirportCitySearchResponder::respondToRequest(
                new AirportCitySearchRequest(
                    $itinerary['destination'],
                ),
                $pdo
            )->getResults()[0];

            array_push(
                $flights,
                new \JAND\Common\Trips\FlightItinerary(
                    $itinerary['itinerary_id'],
                    $outboundSegments,
                    $returnSegments,
                    $origin,
                    $destination,
                    new \DateTime($itinerary['start_date']),
                    new \DateTime($itinerary['end_date']),
                    $itinerary['total_price'],
                    $itinerary['adults'],
                    $itinerary['children'],
                    $itinerary['infants'],
                    (bool) $itinerary['one_way']
                )
            );
        }//end foreach

        $hotelItinerarySelectStmt = $pdo->prepare(
            'SELECT i.*,h.* FROM hotel_itineraries i, hotels h, hotel_bookings b,  sessions s WHERE 
i.itinerary_id=b.itinerary_id AND s.session_token=:sessionToken AND s.user_id=b.user_id AND 
h.hotel_id=i.hotel_id'
        );
        $hotelItinerarySelectStmt->execute(
            ['sessionToken' => $sessionToken]
        );
        $hotelItinerarySelectResults = $hotelItinerarySelectStmt->fetchAll();
        $hotelItinerarySelectStmt->closeCursor();

        foreach ($hotelItinerarySelectResults as &$itinerary) {
            $city = AirportCitySearchResponder::respondToRequest(
                new AirportCitySearchRequest(
                    $itinerary['city'],
                ),
                $pdo
            )->getResults()[0];

            array_push(
                $hotels,
                new \JAND\Common\Trips\HotelItinerary(
                    $itinerary['itinerary_id'],
                    new Hotel($itinerary['hotel_id'], $city, $itinerary['hotel_code'], $itinerary['hotel_name']),
                    new \DateTime($itinerary['check_in']),
                    new \DateTime($itinerary['check_out']),
                    $itinerary['total_price'],
                    $itinerary['adults']
                )
            );
        }

        return new \JAND\Common\Messages\Frontend\GetBookingsResponse($flights, $hotels);

    }//end respondToRequest()


}//end class
