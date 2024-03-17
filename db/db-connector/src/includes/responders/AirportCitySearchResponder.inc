<?php
/**
 * Contains the responder for an airport or city search request.
 *
 * @package JAND\DbConnector\Includes\Responders\AirportCitySearchResponder
 */

namespace JAND\DbConnector\Includes\Responders;

/**
 * Responds to airport or city search requests.
 */
abstract class AirportCitySearchResponder
{


    /**
     * Responds to an airport search request.
     *
     * @param \JAND\Common\Messages\Shared\AirportCitySearchRequest $request Airport search request.
     * @param \PDO                                                  $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Shared\AirportCitySearchResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Shared\AirportCitySearchRequest $request, \PDO $pdo)
    {
        $stmt = $pdo->prepare(
            'SELECT * FROM airport_cities 
WHERE iata_code LIKE UPPER(:query) OR LOWER(name) LIKE LOWER(:query) ORDER BY (iata_code=UPPER(:exact)) DESC'
        );
        $stmt->execute(
            [
                'query' => '%'.$request->getSearchString().'%',
                'exact' => $request->getSearchString(),
            ]
        );
        $results = $stmt->fetchAll();
        $stmt->closeCursor();
        $airportCityList = [];

        foreach ($results as &$result) {
            array_push(
                $airportCityList,
                new \JAND\Common\Trips\AirportCity(
                    $result['iata_code'],
                    $result['name'],
                    $result['latitude'],
                    $result['longitude'],
                    $result['country_code']
                )
            );
        }

        $forcePull = false;
        if (strlen($request->getSearchString()) === 3) {
            if (isset($airportCityList[0]) && $airportCityList[0]->getCode() !== $request->getSearchString()) {
                // User specified a possible IATA code that was not found in DB.
                $forcePull = true;
            }
        }

        if (count($airportCityList) < 1 || $forcePull) {
            // No results found, try API.
            $request  = new \JAND\Common\Messages\Shared\AirportCitySearchRequest($request->getSearchString());
            $response = $request->sendRequest(\JAND\DbConnector\Includes\RabbitClientManager::getClient());

            foreach ($response->getResults() as &$airportCity) {
                // Add to db.
                $stmt = $pdo->prepare(
                    'INSERT INTO airport_cities VALUES 
        (:iataCode, :name, :latitude, :longitude, :countryCode, DEFAULT) ON DUPLICATE KEY UPDATE
iata_code=:iataCode, name=:name, latitude=:latitude, longitude=:longitude, 
country_code=:countryCode'
                );
                    $stmt->execute(
                        [
                            'iataCode'    => $airportCity->getCode(),
                            'name'        => $airportCity->getName(),
                            'latitude'    => $airportCity->getLatitude(),
                            'longitude'   => $airportCity->getLongitude(),
                            'countryCode' => $airportCity->getCountryCode(),
                        ]
                    );
                    $stmt->closeCursor();
            }//end foreach

            $airportCityList = array_merge($response->getResults(), $airportCityList);
        }//end if

        return new \JAND\Common\Messages\Shared\AirportCitySearchResponse($airportCityList);

    }//end respondToRequest()


}//end class
