<?php
/**
 * Runs regularly occuring events.
 *
 * @package JAND\DbConnector\Includes\Responders\RunEventsResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use JAND\Common\Messages\DbConnector\AirlineSearchRequest;
use JAND\Common\Messages\DbConnector\BookingReminderRequest;
use JAND\Common\Messages\DbTimer\RunEventsRequest;
use JAND\Common\Messages\DbTimer\RunEventsResponse;
use JAND\Common\Messages\Shared\AirportCitySearchRequest;
use JAND\Common\Trips\Airline;
use JAND\Common\Trips\AirportCity;
use JAND\Common\Trips\Flight;
use JAND\Common\Trips\FlightItinerary;
use JAND\Common\Trips\Hotel;
use JAND\DbConnector\Includes\GetSegmentInfo;
use JAND\DbConnector\Includes\RabbitClientManager;

/**
 * Runs regularly occuring events.
 */
abstract class RunEventsResponder
{


    /**
     * Check for any booking notifications.
     *
     * @param \PDO $pdo DB PDO.
     *
     * @return void
     */
    private static function checkBookings(\PDO $pdo)
    {
        /**
         * Reminder requests.
         *
         * @var BookingReminderRequest[] $requests Reminder requests.
         */
        $requests = [];

        $flightItinerarySelectStmt = $pdo->prepare(
            'SELECT f.*,u.email,u.user_id FROM flight_itineraries f, flight_bookings b, users u WHERE 
f.itinerary_id=b.itinerary_id AND b.notified=0 AND u.user_id=b.user_id 
AND DATE_SUB(f.start_date, INTERVAL 1 DAY)<=NOW()'
        );
        $flightItinerarySelectStmt->execute();
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
                    GetSegmentInfo::get(
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
                        GetSegmentInfo::get(
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
                $requests,
                new BookingReminderRequest(
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
                    $itinerary['email'],
                    $itinerary['user_id']
                )
            );
        }//end foreach

        $hotelItinerarySelectStmt = $pdo->prepare(
            'SELECT i.*,h.*,u.email,u.user_id FROM hotel_itineraries i, hotels h, hotel_bookings b, users u WHERE 
i.itinerary_id=b.itinerary_id AND  
h.hotel_id=i.hotel_id AND b.notified=0 AND u.user_id=b.user_id 
AND DATE_SUB(i.check_in, INTERVAL 1 DAY)<=NOW()'
        );
        $hotelItinerarySelectStmt->execute();
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
                $requests,
                new BookingReminderRequest(
                    new \JAND\Common\Trips\HotelItinerary(
                        $itinerary['itinerary_id'],
                        new Hotel($itinerary['hotel_id'], $city, $itinerary['hotel_code'], $itinerary['hotel_name']),
                        new \DateTime($itinerary['check_in']),
                        new \DateTime($itinerary['check_out']),
                        $itinerary['total_price'],
                        $itinerary['adults']
                    ),
                    $itinerary['email'],
                    $itinerary['user_id']
                )
            );
        }//end foreach

        foreach ($requests as &$request) {
            RabbitClientManager::sendRequest($request);

            $booking = $request->getItinerary();

            if ($booking instanceof FlightItinerary) {
                $stmt = $pdo->prepare(
                    'UPDATE flight_bookings SET notified=1 WHERE user_id=:userId AND 
itinerary_id=:itineraryId'
                );
            } else {
                $stmt = $pdo->prepare(
                    'UPDATE hotel_bookings SET notified=1 WHERE user_id=:userId AND 
itinerary_id=:itineraryId'
                );
            }

            $stmt->execute(
                [
                    'userId'      => $request->getUserId(),
                    'itineraryId' => $booking->getItineraryId(),
                ]
            );
            $stmt->closeCursor();
        }//end foreach

    }//end checkBookings()


    /**
     * Runs regularly occuring events.
     *
     * @param RunEventsRequest $request Airport search request.
     * @param \PDO             $pdo     PDO instance.
     *
     * @return RunEventsResponse Response to request.
     */
    public static function respondToRequest(RunEventsRequest $request, \PDO $pdo)
    {
        static::checkBookings($pdo);

        return new RunEventsResponse();

    }//end respondToRequest()


}//end class
