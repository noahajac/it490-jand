<?php
/**
 * Request that sets user POI keyword preferences.
 *
 * @package JAND\Common\Messages\Frontend\SetUserKeywordPrefResponse
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Request with selected keywords.
 */
class SetUserKeywordPrefRequest extends SessionRequest
{

    /**
     * Array of POI keywords.
     *
     * @var String[] $keywords Array of keywords.
     */
    private array $keywords;


    /**
     * Creates a get keywords pref set request.
     *
     * @param string   $sessionToken Session token.
     * @param string[] $keywords     Array of keywords.
     */
    public function __construct(string $sessionToken, array $keywords)
    {
        parent::__construct($sessionToken);
        $this->keywords = $keywords;

    }//end __construct()


    /**
     * Gets preferred keywords.
     *
     * @return string[] Array of keywords.
     */
    public function getKeywords()
    {
        return $this->keywords;

    }//end getKeywords()


}//end class
