<?php
/**
 * Response to a get bundles request.
 *
 * @package JAND\Common\Messages\Deploy\GetBundlesResponse
 */

namespace JAND\Common\Messages\Deploy;

/**
 * A get bundles response.
 */
class GetBundlesResponse
{

    /**
     * Array of results.
     *
     * @var \JAND\Common\Deploy\Bundle[] $results Array of results.
     */
    private array $results;


    /**
     * Creates a new bundles list response.
     *
     * @param \JAND\Common\Deploy\Bundle[] $results Results from query.
     */
    public function __construct(array $results)
    {
        $this->results = $results;

    }//end __construct()


    /**
     * Gets the results.
     *
     * @return \JAND\Common\Deploy\Bundle[] List of bundles.
     */
    public function getResults()
    {
        return $this->results;

    }//end getResults()


}//end class
