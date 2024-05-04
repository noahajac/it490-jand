<?php
/**
 * Contains the responder for a create booking request.
 *
 * @package JAND\DbConnector\Includes\Responders\CreateBookingResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use DateTime;
use JAND\Common\Messages\DbConnector\AirlineSearchRequest;
use JAND\Common\Messages\Shared\AirportCitySearchRequest;
use JAND\Common\Messages\Shared\CreateBookingRequest;
use JAND\Common\Trips\Airline;
use JAND\Common\Trips\AirlineReview;
use JAND\Common\Trips\AirportCity;
use JAND\Common\Trips\Flight;
use JAND\Common\Trips\FlightItinerary;
use JAND\Common\Trips\Hotel;
use JAND\Common\Trips\HotelReview;
use JAND\DbConnector\Includes\RabbitClientManager;

/**
 * Responds to create booking requests.
 */
abstract class CreateBookingResponder
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
     * Responds to a create booking request.
     *
     * @param \JAND\Common\Messages\Shared\CreateBookingRequest $request Create request.
     * @param \PDO                                              $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Shared\CreateBookingResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Shared\CreateBookingRequest $request, \PDO $pdo)
    {
        $sessionToken = $request->getSessionToken();
        $booking      = $request->getBooking();

        $stmt = $pdo->prepare(
            'SELECT u.email FROM users u, sessions s WHERE u.user_id=s.user_id AND 
s.session_token=:sessionToken'
        );
        $stmt->execute(
            ['sessionToken' => $sessionToken]
        );
        $stmtResults = $stmt->fetch();
        $email       = $stmtResults['email'];
        $stmt->closeCursor();

        if ($booking instanceof FlightItinerary) {
            $stmt = $pdo->prepare(
                'INSERT INTO flight_bookings VALUES 
    ((SELECT user_id FROM sessions WHERE session_token=:sessionToken), 
    :itineraryId, DEFAULT) 
ON DUPLICATE KEY UPDATE itinerary_id=:itineraryId'
            );

            $stmt->execute(
                [
                    'sessionToken' => $sessionToken,
                    'itineraryId'  => $booking->getItineraryId(),
                ]
            );
            $stmt->closeCursor();

            $flightItinerarySelectStmt = $pdo->prepare(
                'SELECT * FROM flight_itineraries WHERE 
itinerary_id=:itineraryId'
            );
            $flightItinerarySelectStmt->execute(
                ['itineraryId' => $booking->getItineraryId()]
            );
            $itinerary = $flightItinerarySelectStmt->fetch();
            $flightItinerarySelectStmt->closeCursor();

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

            $actualRequest = new CreateBookingRequest(
                $sessionToken,
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
                ),
                $email
            );
        } else {
            $stmt = $pdo->prepare(
                'INSERT INTO hotel_bookings VALUES 
    ((SELECT user_id FROM sessions WHERE session_token=:sessionToken), 
    :itineraryId, DEFAULT) 
ON DUPLICATE KEY UPDATE itinerary_id=:itineraryId'
            );

            $stmt->execute(
                [
                    'sessionToken' => $sessionToken,
                    'itineraryId'  => $booking->getItineraryId(),
                ]
            );
            $stmt->closeCursor();

            $hotelItinerarySelectStmt = $pdo->prepare(
                'SELECT i.*,h.* FROM hotel_itineraries i, hotels h WHERE 
    i.itinerary_id=:itineraryId AND h.hotel_id=i.hotel_id'
            );
            $hotelItinerarySelectStmt->execute(
                ['itineraryId' => $booking->getItineraryId()]
            );
            $itinerary = $hotelItinerarySelectStmt->fetch();
            $hotelItinerarySelectStmt->closeCursor();

            $city          = AirportCitySearchResponder::respondToRequest(
                new AirportCitySearchRequest(
                    $itinerary['city'],
                ),
                $pdo
            )->getResults()[0];
            $actualRequest = new CreateBookingRequest(
                $sessionToken,
                new \JAND\Common\Trips\HotelItinerary(
                    $itinerary['itinerary_id'],
                    new Hotel($itinerary['hotel_id'], $city, $itinerary['hotel_code'], $itinerary['hotel_name']),
                    new \DateTime($itinerary['check_in']),
                    new \DateTime($itinerary['check_out']),
                    $itinerary['total_price'],
                    $itinerary['adults']
                ),
                $email
            );
        }//end if

        RabbitClientManager::sendRequest($actualRequest);

        return new \JAND\Common\Messages\Shared\CreateBookingResponse();

    }//end respondToRequest()


}//end class
