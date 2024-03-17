<?php
/**
 * Contains API call to check airport.
 *
 * @package JAND\Frontend\Api\CheckAirport\Includes\CheckAirport
 */

namespace JAND\Frontend\Api\CheckAirport\Includes;

/**
 * Checks airport input.
 */
abstract class CheckAirport
{


    /**
     * Checks airport input.
     *
     * @return void
     */
    public static function processCheckAirport()
    {
        header('Content-Type: application/json');
        $session = \JAND\Frontend\Includes\SessionManager::getSession();

        if (!$session) {
            http_response_code(401);
            exit();
        }

        $searchString = filter_input(INPUT_GET, 'search', FILTER_SANITIZE_FULL_SPECIAL_CHARS);

        if (empty($searchString)) {
            echo json_encode([]);
            exit();
        }

        $request  = new \JAND\Common\Messages\Shared\AirportCitySearchRequest($searchString);
        $response = $request->sendRequest(\JAND\Frontend\Includes\RabbitClientManager::getClient());

        $airports = [];

        foreach ($response->getResults() as &$airport) {
            array_push(
                $airports,
                [
                    'code'        => $airport->getCode(),
                    'name'        => $airport->getName(),
                    'countryCode' => $airport->getCountryCode(),
                ]
            );
        }

        echo json_encode($airports);
        exit();

    }//end processCheckAirport()


}//end class
