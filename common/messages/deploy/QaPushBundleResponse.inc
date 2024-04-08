<?php
/**
 * Contains response when installing a bundle to QA.
 *
 * @package JAND\Common\Messages\Deploy\QaPushBundleResponse
 */

namespace JAND\Common\Messages\Deploy;

/**
 * A response when installing a bundle to QA.
 */
class QaPushBundleResponse
{

    /**
     * If a real bundle.
     *
     * @var boolean $isBundle Is real bundle.
     */
    private bool $isBundle;


    /**
     * Creates the response.
     *
     * @param boolean $isBundle Is real bundle.
     */
    public function __construct(bool $isBundle)
    {
        $this->isBundle = $isBundle;

    }//end __construct()


    /**
     * Gets if real bundle.
     *
     * @return boolean Is real bundle.
     */
    public function getIsBundle()
    {
        return $this->isBundle;

    }//end getIsBundle()


}//end class
