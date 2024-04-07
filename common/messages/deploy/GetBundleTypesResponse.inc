<?php
/**
 * Response to a get bundle types request.
 *
 * @package JAND\Common\Messages\Deploy\GetBundleTypesResponse
 */

namespace JAND\Common\Messages\Deploy;

/**
 * A get bundle types response.
 */
class GetBundleTypesResponse
{

    /**
     * Array of results.
     *
     * @var \JAND\Common\Deploy\BundleType[] $results Array of results.
     */
    private array $results;


    /**
     * Creates a new bundle types response.
     *
     * @param \JAND\Common\Deploy\BundleType[] $results Results from query.
     */
    public function __construct(array $results)
    {
        $this->results = $results;

    }//end __construct()


    /**
     * Gets the results.
     *
     * @return \JAND\Common\Deploy\BundleType[] Bundle types.
     */
    public function getResults()
    {
        return $this->results;

    }//end getResults()


}//end class
