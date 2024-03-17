<?php
/**
 * Contains the responder for an airline search request.
 *
 * @package JAND\DbConnector\Includes\Responders\AirlineSearchResponder
 */

namespace JAND\DbConnector\Includes\Responders;

/**
 * Responds to airline search requests.
 */
abstract class AirlineSearchResponder
{


    /**
     * Responds to an airline search request.
     *
     * @param \JAND\Common\Messages\DbConnector\AirlineSearchRequest $request Airline search request.
     * @param \PDO                                                   $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\DbConnector\AirlineSearchResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\DbConnector\AirlineSearchRequest $request, \PDO $pdo)
    {
        $stmt = $pdo->prepare(
            'SELECT * FROM airlines 
WHERE LOWER(name) LIKE LOWER(:query) OR iata_code LIKE UPPER(:query)'
        );
        $stmt->execute(['query' => '%'.$request->getSearchString().'%']);
        $results = $stmt->fetchAll();
        $stmt->closeCursor();
        $airlineList = [];

        foreach ($results as &$result) {
            array_push(
                $airlineList,
                new \JAND\Common\Trips\Airline(
                    $result['iata_code'],
                    $result['name'],
                )
            );
        }

        if (count($airlineList) < 1) {
            // No results found, try API.
            $request = new \JAND\Common\Messages\DbConnector\AirlineSearchRequest($request->getSearchString());

            /**
             * Response from DMZ.
             *
             * @var \JAND\Common\Messages\DbConnector\AirlineSearchResponse $response DMZ response.
             */
            $response = $request->sendRequest(\JAND\DbConnector\Includes\RabbitClientManager::getClient());

            foreach ($response->getResults() as &$airline) {
                // Add to db.
                try {
                    $stmt = $pdo->prepare(
                        'INSERT INTO airlines VALUES (:iataCode, :name)'
                    );
                    $stmt->execute(
                        [
                            'iataCode' => $airline->getCode(),
                            'name'     => $airline->getName(),
                        ]
                    );
                    $stmt->closeCursor();
                } catch (\PDOException $e) { // phpcs:ignore Generic.CodeAnalysis.EmptyStatement.DetectedCatch
                    // May already be in DB.
                }
            }//end foreach

            $airlineList = array_merge($airlineList, $response->getResults());
        }//end if

        return new \JAND\Common\Messages\DbConnector\AirlineSearchResponse($airlineList);

    }//end respondToRequest()


}//end class
