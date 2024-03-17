<?php
/**
 * Response that gives user POI keyword preferences.
 *
 * @package JAND\Common\Messages\Frontend\GetUserKeywordPrefResponse
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Response with all POI keywords.
 */
class GetUserKeywordPrefResponse
{

    /**
     * Array of POI keywords.
     *
     * @var string[] $keywords Array of keywords.
     */
    private array $keywords;


    /**
     * Creates a get POI keywords response.
     *
     * @param string[] $keywords Array of keywords.
     */
    public function __construct(array $keywords)
    {
        $this->keywords = $keywords;

    }//end __construct()


    /**
     * Gets POI keywords.
     *
     * @return string[] Array of keywords.
     */
    public function getKeywords()
    {
        return $this->keywords;

    }//end getKeywords()


}//end class
