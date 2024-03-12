<?php
/**
 * Base class for a search response.
 *
 * @package JAND\Common\Messages\Shared\SearchResponse
 */

namespace JAND\Common\Messages\Shared;

/**
 * Base class for a search response.
 */
abstract class SearchResponse
{

    /**
     * Error, if there is one.
     *
     * @var OperationError $error Error message.
     */
    private ?OperationError $error;


    /**
     * Create a new search response.
     *
     * @param OperationError $error Error message.
     */
    protected function __construct(?OperationError $error=null)
    {
        $this->error = $error;

    }//end __construct()


    /**
     * Gets error.
     *
     * @return ?OperationError Error.
     */
    public function getError()
    {
        return $this->error;

    }//end getError()


}//end class
