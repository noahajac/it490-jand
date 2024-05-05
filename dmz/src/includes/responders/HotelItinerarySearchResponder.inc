<?php
/**
 * Contains the responder for a hotel itinerary search request.
 *
 * @package JAND\Dmz\Includes\Responders\HotelItinerarySearchResponder
 */

namespace JAND\Dmz\Includes\Responders;

use JAND\Common\Trips\AirportCity;
use \JAND\Common\Trips\Hotel;

/**
 * Responds to hotel itinerary search requests.
 */
abstract class HotelItinerarySearchResponder
{


    /**
     * Responds to a hotel itinerary search request.
     *
     * @param \JAND\Common\Messages\Shared\HotelItinerarySearchRequest $request Hotel itinerary search request.
     *
     * @return \JAND\Common\Messages\Shared\HotelItinerarySearchRespone Response to request.
     */
    public static function respondToRequest(
        \JAND\Common\Messages\Shared\HotelItinerarySearchRequest $request
    ) {
        $requestUrl      = AmadeusManager::getApiUrl().'/v1/reference-data/locations/hotels/by-city';
        $queryParamsData = [
            'cityCode' => $request->getCity()->getCode(),
            'radius'   => 1,
        ];

        $queryParams = http_build_query($queryParamsData);

        $curl = curl_init($requestUrl.'?'.$queryParams);
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
        curl_setopt(
            $curl,
            CURLOPT_HTTPHEADER,
            [AmadeusManager::getAuthorizationHeader()]
        );

        $results = json_decode(curl_exec($curl))->data;

        curl_close($curl);

        $hotelOfferSearches = [];
        $hotelSearchStr     = null;
        $hotelSearchAmount  = 0;
        foreach ($results as &$result) {
            if (count($hotelOfferSearches) > 0) {
                break;
            }

            // Limit number of hotel searches to improve performance.
            if (empty($hotelSearchStr)) {
                $hotelSearchStr = $result->hotelId;
            } else {
                $hotelSearchStr .= ','.$result->hotelId;
            }

            $hotelSearchAmount++;

            if ($hotelSearchAmount > 5) {
                array_push($hotelOfferSearches, $hotelSearchStr);
                $hotelSearchStr    = null;
                $hotelSearchAmount = 0;
            }
        }//end foreach

        // array_push($hotelOfferSearches, $hotelSearchStr);
        $offerList = [];

        foreach ($hotelOfferSearches as &$hotelOfferSearch) {
            $requestUrl      = AmadeusManager::getApiUrl().'/v3/shopping/hotel-offers';
            $queryParamsData = [
                'hotelIds'     => $hotelOfferSearch,
                'adults'       => $request->getAdults(),
                'checkInDate'  => $request->getStartDate()->format('Y-m-d'),
                'checkOutDate' => $request->getEndDate()->format('Y-m-d'),
                'currency'     => 'USD',
            ];
            $queryParams     = http_build_query($queryParamsData);
            $curl            = curl_init($requestUrl.'?'.$queryParams);
            curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
            curl_setopt(
                $curl,
                CURLOPT_HTTPHEADER,
                [
                    AmadeusManager::getAuthorizationHeader(),
                    'Content-type: application/vnd.amadeus+json',
                    'Accept: application/json, text/plain, */*',
                ]
            );
            $execResults = json_decode(curl_exec($curl));

            echo print_r(curl_getinfo($curl));

            if (!isset($execResults->data)) {
                continue;
            }

            $offerResults = $execResults->data;

            curl_close($curl);

            foreach ($offerResults as &$hotel) {
                foreach ($hotel->offers as &$offer) {
                    try {
                        array_push(
                            $offerList,
                            new \JAND\Common\Trips\HotelItinerary(
                                null,
                                new Hotel(
                                    null,
                                    new AirportCity($hotel->hotel->cityCode, null, null, null, null),
                                    $hotel->hotel->hotelId,
                                    $hotel->hotel->name
                                ),
                                new \DateTime($offer->checkInDate),
                                new \DateTime($offer->checkOutDate),
                                $offer->price->total,
                                $offer->guests->adults
                            )
                        );
                    } catch (\Throwable $th) {
                        continue;
                    }//end try
                }//end foreach
            }//end foreach
        }//end foreach

        echo 'Returning results';

        return new \JAND\Common\Messages\Shared\HotelItinerarySearchResponse($offerList);

    }//end respondToRequest()


}//end class
