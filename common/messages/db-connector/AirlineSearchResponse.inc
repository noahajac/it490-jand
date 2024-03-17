<?php
/**
 * Response to an airline search request.
 *
 * @package JAND\Common\Messages\DbConnector\AirlineSearchResponse
 */

namespace JAND\Common\Messages\DbConnector;

/**
 * An airline search response.
 */
class AirlineSearchResponse extends \JAND\Common\Messages\Shared\SearchResponse
{

    /**
     * Array of results.
     *
     * @var \JAND\Common\Trips\Airline[] $results Array of results.
     */
    private array $results;


    /**
     * Creates a new airline search response.
     *
     * @param \JAND\Common\Trips\Airline[]                $results Results from query.
     * @param \JAND\Common\Messages\Shared\OperationError $error   Error if there is one.
     */
    public function __construct(?array $results, ?\JAND\Common\Messages\Shared\OperationError $error=null)
    {
        $this->results = $results;
        parent::__construct($error);

    }//end __construct()


    /**
     * Check if an IATA code is valid.
     *
     * @param string $iataCode Code to check.
     *
     * @return false|\JAND\Common\Trips\Airline The airline for the code, or false.
     */
    public function checkCode(string $iataCode)
    {
        foreach ($this->results as &$airline) {
            if ($airline->getCode() === $iataCode) {
                return $airline;
            }
        }

        return false;

    }//end checkCode()


    /**
     * Gets the results.
     *
     * @return ?\JAND\Common\Trips\Airline[] Search results.
     */
    public function getResults()
    {
        return $this->results;

    }//end getResults()


}//end class
