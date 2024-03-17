<?php
/**
 * Contains the responder for a POI search request.
 *
 * @package JAND\Dmz\Includes\Responders\PoiSearchResponder
 */

namespace JAND\Dmz\Includes\Responders;

use JAND\Common\Trips\AirportCity;

/**
 * Responds to POI search requests.
 */
abstract class PoiSearchResponder
{


    /**
     * Responds to a POI search request.
     *
     * @param \JAND\Common\Messages\Shared\PoiSearchRequest $request POI search request.
     *
     * @return \JAND\Common\Messages\Shared\PoiSearchResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Shared\PoiSearchRequest $request)
    {
        $requestUrl = AmadeusManager::getApiUrl().'/v1/reference-data/locations/pois';

        $queryParams = http_build_query(
            [
                'latitude'    => $request->getCity()->getLatitude(),
                'longitude'   => $request->getCity()->getLongitude(),
                'radius'      => 20,
                'page[limit]' => 60,
            ]
        );

        $curl = curl_init($requestUrl.'?'.$queryParams);
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
        curl_setopt(
            $curl,
            CURLOPT_HTTPHEADER,
            [AmadeusManager::getAuthorizationHeader()]
        );
        $results = json_decode(curl_exec($curl));
        curl_close($curl);
        $poiList = [];

        if (isset($results->data)) {
            $resultData  = $results->data;
            $resultCount = $results->meta->count;
            $iters       = 1;

            foreach ($resultData as &$result) {
                array_push(
                    $poiList,
                    new \JAND\Common\Trips\Poi(
                        null,
                        $request->getCity(),
                        $result->tags,
                        $result->name,
                    )
                );
            }

            /*
                Pagination doesn't work on the API for some reason.
                while ($resultCount > ($iters * 100)) {
                if ($iters > 10) {
                    break;
                }

                $queryParams = http_build_query(
                    [
                        'latitude'     => $request->getCity()->getLatitude(),
                        'longitude'    => $request->getCity()->getLongitude(),
                        'radius'       => 5,
                        'page[limit]'  => 100,
                        'page[offset]' => (100 * $iters),
                    ]
                );

                $curl = curl_init($requestUrl.'?'.$queryParams);
                curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
                curl_setopt(
                    $curl,
                    CURLOPT_HTTPHEADER,
                    [AmadeusManager::getAuthorizationHeader()]
                );
                $results = json_decode(curl_exec($curl));
                curl_close($curl);
                $resultData = $results->data;
                foreach ($resultData as &$result) {
                    array_push(
                        $poiList,
                        new \JAND\Common\Trips\Poi(
                            null,
                            $request->getCity(),
                            $result->tags,
                            $result->name,
                        )
                    );
                }

                $iters++;
                }
            */
        } else {
            $poiList = [];
        }//end if

                return new \JAND\Common\Messages\Shared\PoiSearchResponse($poiList);

    }//end respondToRequest()


}//end class
