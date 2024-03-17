<?php
/**
 * Contains the responder for a flight itinerary search request.
 *
 * @package JAND\Dmz\Includes\Responders\FlightItinerarySearchResponder
 */

namespace JAND\Dmz\Includes\Responders;

/**
 * Responds to flight itinerary search requests.
 */
abstract class FlightItinerarySearchResponder
{


    /**
     * Responds to a flight itinerary search request.
     *
     * @param \JAND\Common\Messages\Shared\FlightItinerarySearchRequest $request Flight itinerary search request.
     *
     * @return \JAND\Common\Messages\Shared\FlightItinerarySearchRespone Response to request.
     */
    public static function respondToRequest(
        \JAND\Common\Messages\Shared\FlightItinerarySearchRequest $request
    ) {
        $requestUrl      = AmadeusManager::getApiUrl().'/v2/shopping/flight-offers';
        $queryParamsData = [
            'originLocationCode'      => $request->getOrigin()->getCode(),
            'destinationLocationCode' => $request->getDestination()->getCode(),
            'departureDate'           => $request->getStartDate()->format('Y-m-d'),
            'adults'                  => $request->getAdults(),
            'children'                => $request->getChildren(),
            'infants'                 => $request->getInfants(),
        ];
        if (!$request->getOneWay()) {
            $queryParamsData['returnDate'] = $request->getEndDate()->format('Y-m-d');
        }

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
        $offerList = [];
        foreach ($results as &$result) {
            $outbound         = $result->itineraries[0];
            $outboundSegments = [];
            foreach ($outbound->segments as &$segment) {
                foreach ($result->travelerPricings[0]->fareDetailsBySegment as &$segmentFares) {
                    if ($segmentFares->segmentId === $segment->id) {
                        $cabin = $segmentFares->cabin;
                    }
                }

                array_push(
                    $outboundSegments,
                    new \JAND\Common\Trips\Flight(
                        null,
                        new \JAND\Common\Trips\AirportCity(
                            $segment->departure->iataCode,
                            null,
                            null,
                            null,
                            null,
                            null
                        ),
                        new \JAND\Common\Trips\AirportCity(
                            $segment->arrival->iataCode,
                            null,
                            null,
                            null,
                            null,
                            null
                        ),
                        new \DateTime($segment->departure->at),
                        new \DateTime($segment->arrival->at),
                        new \JAND\Common\Trips\Airline($segment->carrierCode, null),
                        intval($segment->number),
                        $cabin
                    )
                );
            }//end foreach

            $inbound        = null;
            $returnSegments = null;
            $endDate        = null;
            if (!$request->getOneWay()) {
                $inbound        = $result->itineraries[1];
                $returnSegments = [];
                foreach ($inbound->segments as &$segment) {
                    foreach ($result->travelerPricings[0]->fareDetailsBySegment as &$segmentFares) {
                        if ($segmentFares->segmentId === $segment->id) {
                            $cabin = $segmentFares->cabin;
                        }
                    }

                    array_push(
                        $returnSegments,
                        new \JAND\Common\Trips\Flight(
                            null,
                            new \JAND\Common\Trips\AirportCity(
                                $segment->departure->iataCode,
                                null,
                                null,
                                null,
                                null,
                                null
                            ),
                            new \JAND\Common\Trips\AirportCity(
                                $segment->arrival->iataCode,
                                null,
                                null,
                                null,
                                null,
                                null
                            ),
                            new \DateTime($segment->departure->at),
                            new \DateTime($segment->arrival->at),
                            new \JAND\Common\Trips\Airline($segment->carrierCode, null),
                            intval($segment->number),
                            $cabin
                        )
                    );
                }//end foreach

                $endDate = end($returnSegments)->getArrivalTime();
            } else {
                $endDate = end($outboundSegments)->getArrivalTime();
            }//end if

            array_push(
                $offerList,
                new \JAND\Common\Trips\FlightItinerary(
                    null,
                    $outboundSegments,
                    $returnSegments,
                    $request->getOrigin(),
                    $request->getDestination(),
                    $outboundSegments[0]->getDepartTime(),
                    $endDate,
                    $result->price->grandTotal,
                    $request->getAdults(),
                    $request->getChildren(),
                    $request->getInfants(),
                    $request->getOneWay()
                )
            );
        }//end foreach

        return new \JAND\Common\Messages\Shared\FlightItinerarySearchResponse($offerList);

    }//end respondToRequest()


}//end class
