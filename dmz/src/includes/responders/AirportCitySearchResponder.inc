<?php
/**
 * Contains the responder for an airport search request.
 *
 * @package JAND\Dmz\Includes\Responders\AirportCitySearchResponder
 */

namespace JAND\Dmz\Includes\Responders;

/**
 * Responds to airport or city search requests.
 */
abstract class AirportCitySearchResponder
{


    /**
     * Responds to an airport search request.
     *
     * @param \JAND\Common\Messages\Shared\AirportCitySearchRequest $request Airport search request.
     *
     * @return \JAND\Common\Messages\Shared\AirportCitySearchResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Shared\AirportCitySearchRequest $request)
    {
        $requestUrl  = AmadeusManager::getApiUrl().'/v1/reference-data/locations';
        $queryParams = http_build_query(
            [
                'subType' => 'AIRPORT,CITY',
                'keyword' => $request->getSearchString(),
                'view'    => 'FULL',
            ]
        );

        $curl = curl_init($requestUrl.'?'.$queryParams);
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
        curl_setopt(
            $curl,
            CURLOPT_HTTPHEADER,
            [AmadeusManager::getAuthorizationHeader()]
        );
        $results = json_decode(curl_exec($curl))->data;
        curl_close($curl);
        $airportCityList = [];
        foreach ($results as &$result) {
            array_push(
                $airportCityList,
                new \JAND\Common\Trips\AirportCity(
                    $result->iataCode,
                    ucwords(strtolower($result->name)),
                    $result->geoCode->latitude,
                    $result->geoCode->longitude,
                    $result->address->stateCode,
                    $result->address->countryCode
                )
            );
        }

        return new \JAND\Common\Messages\Shared\AirportCitySearchResponse($airportCityList);

    }//end respondToRequest()


}//end class
