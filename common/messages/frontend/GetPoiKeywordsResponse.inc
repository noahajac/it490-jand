<?php
/**
 * Response that gives all POI keywords.
 *
 * @package JAND\Common\Messages\Frontend\GetPoiKeywordsResponse
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Response with all POI keywords.
 */
class GetPoiKeywordsResponse
{

    /**
     * Array of POI keywords.
     *
     * @var String[] $keywords Array of keywords.
     */
    private array $keywords;


    /**
     * Creates a get POI keywords response.
     *
     * @param String[] $keywords Array of keywords.
     */
    public function __construct(array $keywords)
    {
        $this->keywords = $keywords;

    }//end __construct()


    /**
     * Gets POI keywords.
     *
     * @return String[] Array of keywords.
     */
    public function getKeywords()
    {
        return $this->keywords;

    }//end getKeywords()


}//end class
