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
WHERE LOWER(name) LIKE LOWER(:query) OR iata_code LIKE UPPER(:query)'
        );
        $stmt->execute(['query' => '%'.$request->getSearchString().'%']);
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
                    $result['state_code'],
                    $result['country_code']
                )
            );
        }

        if (count($airportCityList) < 1) {
            // No results found, try API.
            $request  = new \JAND\Common\Messages\Shared\AirportCitySearchRequest($request->getSearchString());
            $response = $request->sendRequest(\JAND\DbConnector\Includes\RabbitClientManager::getClient());

            foreach ($response->getResults() as &$airportCity) {
                // Add to db.
                try {
                    $stmt = $pdo->prepare(
                        'INSERT INTO airport_cities VALUES 
        (:iataCode, :name, :latitude, :longitude, :stateCode, :countryCode, DEFAULT)'
                    );
                    $stmt->execute(
                        [
                            'iataCode'    => $airportCity->getCode(),
                            'name'        => $airportCity->getName(),
                            'latitude'    => $airportCity->getLatitude(),
                            'longitude'   => $airportCity->getLongitude(),
                            'stateCode'   => $airportCity->getStateCode(),
                            'countryCode' => $airportCity->getCountryCode(),
                        ]
                    );
                    $stmt->closeCursor();
                } catch (\PDOException $e) { // phpcs:ignore Generic.CodeAnalysis.EmptyStatement.DetectedCatch
                    // May already be in DB.
                }
            }//end foreach

            $airportCityList = array_merge($airportCityList, $response->getResults());
        }//end if

        return new \JAND\Common\Messages\Shared\AirportCitySearchResponse($airportCityList);

    }//end respondToRequest()


}//end class
