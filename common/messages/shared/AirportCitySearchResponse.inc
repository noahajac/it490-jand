<?php
/**
 * Response to an airport search request.
 *
 * @package JAND\Common\Messages\Shared\AirportCitySearchResponse
 */

namespace JAND\Common\Messages\Shared;

/**
 * An airport search response.
 */
class AirportCitySearchResponse extends SearchResponse
{

    /**
     * Array of results.
     *
     * @var \JAND\Common\Trips\AirportCity[] $results Array of results.
     */
    private array $results;


    /**
     * Creates a new airport search response.
     *
     * @param AirportCity[]  $results Results from query.
     * @param OperationError $error   Error if there is one.
     */
    public function __construct(?array $results, ?OperationError $error=null)
    {
        $this->results = $results;
        parent::__construct($error);

    }//end __construct()


    /**
     * Check if an IATA code is valid.
     *
     * @param string $iataCode Code to check.
     *
     * @return false|\JAND\Common\Trips\AirportCity The city for the code, or false.
     */
    public function checkCode(string $iataCode)
    {
        foreach ($this->results as &$city) {
            if ($city->getCode() === $iataCode) {
                return $city;
            }
        }

        return false;

    }//end checkCode()


    /**
     * Gets the results.
     *
     * @return ?\JAND\Common\Trips\AirportCity[] Search results.
     */
    public function getResults()
    {
        return $this->results;

    }//end getResults()


}//end class
