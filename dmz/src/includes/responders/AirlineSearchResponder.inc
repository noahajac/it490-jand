<?php
/**
 * Contains the responder for an airline search request.
 *
 * @package JAND\Dmz\Includes\Responders\AirlineSearchResponder
 */

namespace JAND\Dmz\Includes\Responders;

/**
 * Responds to airline search requests.
 */
abstract class AirlineSearchResponder
{


    /**
     * Responds to an airline search request.
     *
     * @param \JAND\Common\Messages\DbConnector\AirlineSearchRequest $request Airline search request.
     *
     * @return \JAND\Common\Messages\DbConnector\AirlineSearchResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\DbConnector\AirlineSearchRequest $request)
    {
        $requestUrl  = AmadeusManager::getApiUrl().'/v1/reference-data/airlines';
        $queryParams = http_build_query(
            [
                'airlineCodes' => $request->getSearchString(),
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
        $airlineList = [];
        foreach ($results as &$result) {
            array_push(
                $airlineList,
                new \JAND\Common\Trips\Airline(
                    $result->iataCode,
                    ucwords(strtolower($result->businessName)),
                )
            );
        }

        return new \JAND\Common\Messages\DbConnector\AirlineSearchResponse($airlineList);

    }//end respondToRequest()


}//end class
