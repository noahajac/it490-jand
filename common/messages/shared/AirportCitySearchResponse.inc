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
     * Gets the results.
     *
     * @return ?AirportCity[] Search results.
     */
    public function getResults()
    {
        return $this->results;

    }//end getResults()


}//end class
