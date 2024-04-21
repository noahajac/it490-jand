<?php
/**
 * Contains the responder for a flight itinerary search request.
 *
 * @package JAND\DbConnector\Includes\Responders\FlightItinerarySearchResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use JAND\Common\Messages\DbConnector\AirlineSearchRequest;
use JAND\Common\Messages\Shared\AirportCitySearchRequest;
use JAND\Common\Trips\Flight;
use JAND\Common\Trips\AirportCity;
use JAND\Common\Trips\Airline;
use JAND\Common\Trips\FlightItinerary;


/**
 * Responds to flight itinerary search requests.
 */
abstract class FlightItinerarySearchResponder
{


    /**
     * Takes a flight and gets airport and airline info.
     * Adds flight to DB and get DB.
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

        $addFlightStatement = $pdo->prepare(
            'INSERT INTO flights VALUES 
(null, :departAirport, :arrivalAirport, :departTime, :arrivalTime, :airline, :flightNo, :className, DEFAULT) 
ON DUPLICATE KEY UPDATE depart_airport=:departAirport, arrival_airport=:arrivalAirport, depart_time=:departTime, 
arrival_time=:arrivalTime, airline=:airline, flight_no=:flightNo, class_name=:className, 
flight_id=LAST_INSERT_ID(flight_id)'
        );
        $addFlightStatement->execute(
            [
                'departAirport'  => $departAirport->getCode(),
                'arrivalAirport' => $arrivalAirport->getCode(),
                'departTime'     => $segment->getDepartTime()->format('Y-m-d H:i:s'),
                'arrivalTime'    => $segment->getArrivalTime()->format('Y-m-d H:i:s'),
                'airline'        => $airline->getCode(),
                'flightNo'       => $segment->getFlightNo(),
                'className'      => $segment->getClassName(),
            ]
        );
        $flightId = $pdo->lastInsertId();
        $addFlightStatement->closeCursor();

        return new Flight(
            $flightId,
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
     * Checks whether an itinerary and its segments
     * already exist in the DB.
     *
     * @param AirportCity     $origin           Origin airport.
     * @param AirportCity     $destination      Destination airport.
     * @param FlightItinerary $itinerary        Flight itinerary.
     * @param Flight[]        $outboundSegments Outbound flight segments.
     * @param Flight[]        $returnSegments   Return segment on round trip.
     * @param \PDO            $pdo              DB PDO object.
     *
     * @return false|integer False if itinerary doesn't exist. If it does, ID of it.
     */
    private static function checkItineraryExistence(
        AirportCity $origin,
        AirportCity $destination,
        FlightItinerary $itinerary,
        array $outboundSegments,
        ?array $returnSegments,
        \PDO $pdo
    ) {
        // First, see if the itinerary even exists.
        $checkItineraryStmt = $pdo->prepare(
            'SELECT * FROM flight_itineraries WHERE
origin=:origin AND destination=:destination AND start_date=:startDate AND end_date=:endDate AND 
total_price=:totalPrice AND adults=:adults AND children=:children AND 
infants=:infants AND one_way=:oneWay'
        );
        $checkItineraryStmt->execute(
            [
                'origin'      => $origin->getCode(),
                'destination' => $destination->getCode(),
                'startDate'   => $itinerary->getStartDate()->format('Y-m-d'),
                'endDate'     => $itinerary->getEndDate()->format('Y-m-d'),
                'totalPrice'  => $itinerary->getGrandTotal(),
                'adults'      => $itinerary->getAdults(),
                'children'    => $itinerary->getChildren(),
                'infants'     => $itinerary->getInfants(),
                'oneWay'      => (int) $itinerary->getOneWay(),
            ]
        );
        $checkItineraryResults = $checkItineraryStmt->fetchAll();
        $checkItineraryStmt->closeCursor();

        if (count($checkItineraryResults) < 1) {
            // Itinerary doesn't exist.
            return false;
        }

        // Itinerary exists in some form, now check outbound segments.
        $matchedItinerary = false;
        foreach ($checkItineraryResults as &$fetchItineraryResult) {
            $itineraryMatches = true;
            $segmentIndex     = 0;

            foreach ($outboundSegments as &$segment) {
                $getOutboundSegmentsStmt = $pdo->prepare(
                    'SELECT * FROM itinerary_out_segments WHERE 
itinerary_id=:itineraryId AND flight_id=:flightId AND position=:position'
                );
                $getOutboundSegmentsStmt->execute(
                    [
                        'itineraryId' => $fetchItineraryResult['itinerary_id'],
                        'flightId'    => $segment->getFlightId(),
                        'position'    => $segmentIndex,
                    ]
                );
                $segmentFetch = $getOutboundSegmentsStmt->fetch();
                $getOutboundSegmentsStmt->closeCursor();

                // An outbound segment didn't match.
                if ($segmentFetch === false) {
                    $itineraryMatches = false;
                    break;
                }

                $segmentIndex++;
            }//end foreach

            if ($itineraryMatches === false) {
                continue;
            } else if ($itinerary->getOneWay()) {
                $matchedItinerary = $fetchItineraryResult;
                break;
            }

            // Outbound matches, now check return.
            $itineraryMatches = true;
            $segmentIndex     = 0;

            foreach ($returnSegments as &$segment) {
                $getReturnSegmentsStmt = $pdo->prepare(
                    'SELECT * FROM itinerary_return_segments WHERE 
itinerary_id=:itineraryId AND flight_id=:flightId AND position=:position'
                );
                $getReturnSegmentsStmt->execute(
                    [
                        'itineraryId' => $fetchItineraryResult['itinerary_id'],
                        'flightId'    => $segment->getFlightId(),
                        'position'    => $segmentIndex,
                    ]
                );
                $segmentFetch = $getReturnSegmentsStmt->fetch();
                $getReturnSegmentsStmt->closeCursor();

                // A return segment didn't match.
                if ($segmentFetch === false) {
                    $itineraryMatches = false;
                    break;
                }

                $segmentIndex++;
            }//end foreach

            if ($itineraryMatches === false) {
                continue;
            } else {
                $matchedItinerary = $fetchItineraryResult;
                break;
            }
        }//end foreach

        if ($matchedItinerary === false) {
            // No itineraries matched the segments.
            return false;
        }

        return $matchedItinerary['itinerary_id'];

    }//end checkItineraryExistence()


    /**
     * Responds to a flight itinerary search request.
     *
     * @param \JAND\Common\Messages\Shared\FlightItinerarySearchRequest $request Flight itinerary search request.
     * @param \PDO                                                      $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Shared\FlightItinerarySearchResponse Response to request.
     */
    public static function respondToRequest(
        \JAND\Common\Messages\Shared\FlightItinerarySearchRequest $request,
        \PDO $pdo
    ) {
        /*
         * Check db for an existing version of this query within a time frame.
         * If it exists, run a SELECT to craft the response.
         *
         * If not, send to DMZ. Once results received, add to DB, and reply.
         */

        $pastQueryCheck = $pdo->prepare(
            'SELECT COUNT(*) FROM flight_queries 
WHERE origin = :origin 
AND destination = :destination 
AND start_date = :startDate 
AND end_date = :endDate 
AND adults = :adults 
AND children = :children 
AND infants = :infants 
AND one_way = :oneWay 
AND NOW() < pulled_on + INTERVAL 1 DAY'
        );

        $pastQueryCheck->execute(
            [
                'origin'      => $request->getOrigin()->getCode(),
                'destination' => $request->getDestination()->getCode(),
                'startDate'   => $request->getStartDate()->format('Y-m-d'),
                'endDate'     => $request->getEndDate()->format('Y-m-d'),
                'adults'      => $request->getAdults(),
                'children'    => $request->getChildren(),
                'infants'     => $request->getInfants(),
                'oneWay'      => (int) $request->getOneWay(),
            ]
        );

        $pastQueryResult = $pastQueryCheck->fetch();
        $pastQueryCheck->closeCursor();

        $itineraries = [];

        if ($pastQueryResult[0] < 1) {
            // Query was not made recently, pull from DMZ.
            /**
             * Response from DMZ.
             *
             * @var \JAND\Common\Messages\Shared\FlightItinerarySearchResponse $dmzResult
             */
            $dmzResult = \JAND\DbConnector\Includes\RabbitClientManager::sendRequest($request);

            foreach ($dmzResult->getFlightItineraries() as &$itinerary) {
                $outboundSegments = [];
                foreach ($itinerary->getOutboundSegments() as &$segment) {
                    array_push(
                        $outboundSegments,
                        static::getSegmentInfo($segment, $pdo)
                    );
                }//end foreach

                $returnSegments = null;
                if (!$itinerary->getOneWay()) {
                    $returnSegments = [];
                    foreach ($itinerary->getReturnSegments() as &$segment) {
                        array_push(
                            $returnSegments,
                            static::getSegmentInfo($segment, $pdo)
                        );
                    }
                }

                $origin      = AirportCitySearchResponder::respondToRequest(
                    new AirportCitySearchRequest(
                        $itinerary->getOrigin()->getCode(),
                    ),
                    $pdo
                )->getResults()[0];
                $destination = AirportCitySearchResponder::respondToRequest(
                    new AirportCitySearchRequest(
                        $itinerary->getDestination()->getCode(),
                    ),
                    $pdo
                )->getResults()[0];

                $existingItinerary = static::checkItineraryExistence(
                    $origin,
                    $destination,
                    $itinerary,
                    $outboundSegments,
                    $returnSegments,
                    $pdo
                );

                // Itinerary does not exist in DB, add it.
                if ($existingItinerary === false) {
                    $addItineraryStmt = $pdo->prepare(
                        'INSERT INTO flight_itineraries VALUES 
    (null, :origin, :destination, :startDate, :endDate, :totalPrice, :adults, :children, :infants, :oneWay, DEFAULT)'
                    );
                    $addItineraryStmt->execute(
                        [
                            'origin'      => $origin->getCode(),
                            'destination' => $destination->getCode(),
                            'startDate'   => $itinerary->getStartDate()->format('Y-m-d'),
                            'endDate'     => $itinerary->getEndDate()->format('Y-m-d'),
                            'totalPrice'  => $itinerary->getGrandTotal(),
                            'adults'      => $itinerary->getAdults(),
                            'children'    => $itinerary->getChildren(),
                            'infants'     => $itinerary->getInfants(),
                            'oneWay'      => (int) $itinerary->getOneWay(),
                        ]
                    );
                    $itineraryId = $pdo->lastInsertId();

                    $addItineraryStmt->closeCursor();

                    $segmentIndex = 0;
                    foreach ($outboundSegments as &$segment) {
                        $segmentAddStmt = $pdo->prepare(
                            'INSERT INTO itinerary_out_segments VALUES 
    (:itineraryId, :flightId, :position)'
                        );
                        $segmentAddStmt->execute(
                            [
                                'itineraryId' => $itineraryId,
                                'flightId'    => $segment->getFlightId(),
                                'position'    => $segmentIndex,
                            ]
                        );
                        $segmentAddStmt->closeCursor();
                        $segmentIndex++;
                    }

                    if (!$itinerary->getOneWay()) {
                        $segmentIndex = 0;
                        foreach ($returnSegments as &$segment) {
                            $segmentAddStmt = $pdo->prepare(
                                'INSERT INTO itinerary_return_segments VALUES 
    (:itineraryId, :flightId, :position)'
                            );
                            $segmentAddStmt->execute(
                                [
                                    'itineraryId' => $itineraryId,
                                    'flightId'    => $segment->getFlightId(),
                                    'position'    => $segmentIndex,
                                ]
                            );
                            $segmentAddStmt->closeCursor();
                            $segmentIndex++;
                        }
                    }
                } else {
                    $itineraryId = $existingItinerary;
                }//end if

                array_push(
                    $itineraries,
                    new \JAND\Common\Trips\FlightItinerary(
                        $itineraryId,
                        $outboundSegments,
                        $returnSegments,
                        $origin,
                        $destination,
                        $itinerary->getStartDate(),
                        $itinerary->getEndDate(),
                        $itinerary->getGrandTotal(),
                        $itinerary->getAdults(),
                        $itinerary->getChildren(),
                        $itinerary->getInfants(),
                        $itinerary->getOneWay()
                    )
                );
            }//end foreach

            // Add to flight queries log.
            $flightQueriesInsertStmt = $pdo->prepare(
                'INSERT INTO flight_queries VALUES 
(:origin, :destination, :startDate, :endDate, :adults, :children, :infants, :oneWay, DEFAULT)  
ON DUPLICATE KEY UPDATE origin=:origin, destination=:destination, start_date=:startDate, 
end_date=:endDate, adults=:adults, 
children=:children, infants=:infants, one_way=:oneWay'
            );

            $flightQueriesInsertStmt->execute(
                [
                    'origin'      => $request->getOrigin()->getCode(),
                    'destination' => $request->getDestination()->getCode(),
                    'startDate'   => $request->getStartDate()->format('Y-m-d'),
                    'endDate'     => $request->getEndDate()->format('Y-m-d'),
                    'adults'      => $request->getAdults(),
                    'children'    => $request->getChildren(),
                    'infants'     => $request->getInfants(),
                    'oneWay'      => (int) $request->getOneWay(),
                ]
            );
            $flightQueriesInsertStmt->closeCursor();
        } else {
            // Query was made recently, pull from DB.
            $flightItinerarySelectStmt = $pdo->prepare(
                'SELECT * FROM flight_itineraries WHERE 
origin=:origin AND destination=:destination AND start_date=:startDate AND end_date=:endDate AND 
adults=:adults AND children=:children AND 
infants=:infants and one_way=:oneWay'
            );
            $flightItinerarySelectStmt->execute(
                [
                    'origin'      => $request->getOrigin()->getCode(),
                    'destination' => $request->getDestination()->getCode(),
                    'startDate'   => $request->getStartDate()->format('Y-m-d'),
                    'endDate'     => $request->getEndDate()->format('Y-m-d'),
                    'adults'      => $request->getAdults(),
                    'children'    => $request->getChildren(),
                    'infants'     => $request->getInfants(),
                    'oneWay'      => (int) $request->getOneWay(),
                ]
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
                    $itineraries,
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
        }//end if

        return new \JAND\Common\Messages\Shared\FlightItinerarySearchResponse($itineraries);

    }//end respondToRequest()


}//end class
