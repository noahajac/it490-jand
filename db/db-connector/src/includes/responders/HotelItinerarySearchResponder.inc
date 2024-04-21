<?php
/**
 * Contains the responder for a hotel itinerary search request.
 *
 * @package JAND\DbConnector\Includes\Responders\HotelItinerarySearchResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use JAND\Common\Messages\Shared\AirportCitySearchRequest;
use JAND\Common\Trips\Hotel;
use JAND\Common\Trips\AirportCity;
use JAND\Common\Trips\Airline;
use JAND\Common\Trips\HotelItinerary;


/**
 * Responds to hotel itinerary search requests.
 */
abstract class HotelItinerarySearchResponder
{


    /**
     * Takes a hotel and gets city info.
     * Adds hotel to DB and get DB.
     *
     * @param Hotel $hotel Hotel from DMZ.
     * @param \PDO  $pdo   PDO for DB access.
     *
     * @return Hotel Hotel with all information filled.
     */
    private static function getHotelInfo(Hotel $hotel, \PDO $pdo)
    {
        $city = AirportCitySearchResponder::respondToRequest(
            new AirportCitySearchRequest(
                $hotel->getCity()->getCode(),
            ),
            $pdo
        )->getResults()[0];

        $addHotelStatement = $pdo->prepare(
            'INSERT INTO hotels VALUES 
(null, :hotelCode, :hotelName, :city, DEFAULT) 
ON DUPLICATE KEY UPDATE hotel_code=:hotelCode, hotel_name=:hotelName, city=:city, 
hotel_id=LAST_INSERT_ID(hotel_id)'
        );
        $addHotelStatement->execute(
            [
                'hotelCode' => $hotel->getHotelCode(),
                'hotelName' => $hotel->getName(),
                'city'      => $city->getCode(),
            ]
        );
        $hotelId = $pdo->lastInsertId();
        $addHotelStatement->closeCursor();

        return new Hotel(
            $hotelId,
            $city,
            $hotel->getHotelCode(),
            $hotel->getName()
        );

    }//end getHotelInfo()


    /**
     * Checks whether an itinerary and its hotel
     * already exist in the DB.
     *
     * @param HotelItinerary $itinerary Hotel itinerary.
     * @param \PDO           $pdo       DB PDO object.
     *
     * @return false|integer False if itinerary doesn't exist. If it does, ID of it.
     */
    private static function checkItineraryExistence(
        HotelItinerary $itinerary,
        \PDO $pdo
    ) {
        // First, see if the itinerary even exists.
        $checkItineraryStmt = $pdo->prepare(
            'SELECT * FROM hotel_itineraries WHERE
check_in=:checkIn AND check_out=:checkOut AND 
total_price=:totalPrice AND adults=:adults'
        );
        $checkItineraryStmt->execute(
            [
                'checkIn'    => $itinerary->getStartDate()->format('Y-m-d'),
                'checkOut'   => $itinerary->getEndDate()->format('Y-m-d'),
                'totalPrice' => $itinerary->getGrandTotal(),
                'adults'     => $itinerary->getAdults(),
            ]
        );
        $checkItineraryResults = $checkItineraryStmt->fetchAll();
        $checkItineraryStmt->closeCursor();

        if (count($checkItineraryResults) < 1) {
            // Itinerary doesn't exist.
            return false;
        }

        // Itinerary exists in some form, now check the hotel.
        foreach ($checkItineraryResults as &$fetchItineraryResult) {
                $getHotelStmt = $pdo->prepare(
                    'SELECT * FROM hotels WHERE hotel_code=:hotelCode AND 
hotel_name=:hotelName AND city=:city AND hotel_id=:hotelId'
                );
                $getHotelStmt->execute(
                    [
                        'hotelId'   => $fetchItineraryResult['hotel_id'],
                        'hotelCode' => $itinerary->getHotel()->getHotelCode(),
                        'hotelName' => $itinerary->getHotel()->getName(),
                        'city'      => $itinerary->getHotel()->getCity()->getCode(),
                    ]
                );
                $hotelFetch = $getHotelStmt->fetch();
                $getHotelStmt->closeCursor();

            if ($hotelFetch === false) {
                continue;
            } else {
                return $fetchItineraryResult['itinerary_id'];
            }
        }//end foreach

        return false;

    }//end checkItineraryExistence()


    /**
     * Responds to a hotel itinerary search request.
     *
     * @param \JAND\Common\Messages\Shared\HotelItinerarySearchRequest $request Hotel itinerary search request.
     * @param \PDO                                                     $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Shared\HotelItinerarySearchResponse Response to request.
     */
    public static function respondToRequest(
        \JAND\Common\Messages\Shared\HotelItinerarySearchRequest $request,
        \PDO $pdo
    ) {
        /*
         * Check db for an existing version of this query within a time frame.
         * If it exists, run a SELECT to craft the response.
         *
         * If not, send to DMZ. Once results received, add to DB, and reply.
         */

        $pastQueryCheck = $pdo->prepare(
            'SELECT COUNT(*) FROM hotel_queries 
WHERE city = :city 
AND check_in = :checkIn 
AND check_out = :checkOut 
AND NOW() < pulled_on + INTERVAL 1 DAY'
        );

        $pastQueryCheck->execute(
            [
                'city'     => $request->getCity()->getCode(),
                'checkIn'  => $request->getStartDate()->format('Y-m-d'),
                'checkOut' => $request->getEndDate()->format('Y-m-d'),
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
             * @var \JAND\Common\Messages\Shared\HotelItinerarySearchResponse $dmzResult
             */
            $dmzResult = \JAND\DbConnector\Includes\RabbitClientManager::sendRequest($request);

            foreach ($dmzResult->getHotelItineraries() as &$itinerary) {
                $existingItinerary = static::checkItineraryExistence(
                    $itinerary,
                    $pdo
                );

                $hotel = static::getHotelInfo($itinerary->getHotel(), $pdo);

                // Itinerary does not exist in DB, add it.
                if ($existingItinerary === false) {
                    $addItineraryStmt = $pdo->prepare(
                        'INSERT INTO hotel_itineraries VALUES 
    (null, :hotelId, :checkIn, :checkOut, :adults, :totalPrice, DEFAULT)'
                    );
                    $addItineraryStmt->execute(
                        [
                            'hotelId'    => $hotel->getHotelId(),
                            'checkIn'    => $itinerary->getStartDate()->format('Y-m-d'),
                            'checkOut'   => $itinerary->getEndDate()->format('Y-m-d'),
                            'adults'     => $itinerary->getAdults(),
                            'totalPrice' => $itinerary->getGrandTotal(),
                        ]
                    );
                    $itineraryId = $pdo->lastInsertId();

                    $addItineraryStmt->closeCursor();
                } else {
                    $itineraryId = $existingItinerary;
                }//end if

                array_push(
                    $itineraries,
                    new \JAND\Common\Trips\HotelItinerary(
                        $itineraryId,
                        $hotel,
                        $itinerary->getStartDate(),
                        $itinerary->getEndDate(),
                        $itinerary->getGrandTotal(),
                        $itinerary->getAdults()
                    )
                );
            }//end foreach

            // Add to hotel queries log.
            $hotelQueriesInsertStmt = $pdo->prepare(
                'INSERT INTO hotel_queries VALUES 
(:city, :checkIn, :checkOut, :adults, DEFAULT)  
ON DUPLICATE KEY UPDATE city=:city, check_in=:checkIn, check_out=:checkOut, adults=:adults'
            );

            $hotelQueriesInsertStmt->execute(
                [
                    'city'     => $request->getCity()->getCode(),
                    'checkIn'  => $request->getStartDate()->format('Y-m-d'),
                    'checkOut' => $request->getEndDate()->format('Y-m-d'),
                    'adults'   => $request->getAdults(),
                ]
            );
            $hotelQueriesInsertStmt->closeCursor();
        } else {
            // Query was made recently, pull from DB.
            $hotelItinerarySelectStmt = $pdo->prepare(
                'SELECT * FROM hotel_itineraries i, hotels h WHERE 
i.check_in=:checkIn AND i.check_out=:checkOut AND i.adults=:adults AND 
i.hotel_id=h.hotel_id AND h.city=:city'
            );
            $hotelItinerarySelectStmt->execute(
                [
                    'city'     => $request->getCity()->getCode(),
                    'checkIn'  => $request->getStartDate()->format('Y-m-d'),
                    'checkOut' => $request->getEndDate()->format('Y-m-d'),
                    'adults'   => $request->getAdults(),
                ]
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
                    $itineraries,
                    new \JAND\Common\Trips\HotelItinerary(
                        $itinerary['itinerary_id'],
                        new Hotel($itinerary['hotel_id'], $city, $itinerary['hotel_code'], $itinerary['hotel_name']),
                        new \DateTime($itinerary['check_in']),
                        new \DateTime($itinerary['check_out']),
                        $itinerary['total_price'],
                        $itinerary['adults']
                    )
                );
            }//end foreach
        }//end if

        return new \JAND\Common\Messages\Shared\HotelItinerarySearchResponse($itineraries);

    }//end respondToRequest()


}//end class
