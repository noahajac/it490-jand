<?php
/**
 * Contains request definition for a search.
 *
 * @package JAND\Common\Messages\Shared\SearchRequest
 */

namespace JAND\Common\Messages\Shared;

/**
 * A request to search for something.
 */
abstract class SearchRequest extends \JAND\Common\Messages\Request
{

    /**
     * Search string from user.
     *
     * @var string $searchString Search string.
     */
    private string $searchString;


    /**
     * Creates a new search request.
     *
     * @param string $searchString Search string from user.
     * */
    public function __construct(string $searchString)
    {
        $this->searchString = $searchString;

    }//end __construct()


    /**
     * Gets search string.
     *
     * @return string Search string.
     */
    public function getSearchString()
    {
        return $this->searchString;

    }//end getSearchString()


}//end class
