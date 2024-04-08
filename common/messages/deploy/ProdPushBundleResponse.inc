<?php
/**
 * Contains response when installing a bundle to prod.
 *
 * @package JAND\Common\Messages\Deploy\ProdPushBundleResponse
 */

namespace JAND\Common\Messages\Deploy;

/**
 * A response when installing a bundle to prod.
 */
class ProdPushBundleResponse extends QaPushBundleResponse
{

    /**
     * If the bundle passed QA.
     *
     * @var boolean $isPassed Bundle passed QA.
     */
    private bool $isPassed;


    /**
     * Creates the response.
     *
     * @param boolean $isBundle Is real bundle.
     * @param boolean $isPassed Bundle passed QA.
     */
    public function __construct(bool $isBundle, bool $isPassed)
    {
        $this->isPassed = $isPassed;
        parent::__construct($isBundle);

    }//end __construct()


    /**
     * Gets if passed QA.
     *
     * @return boolean Bundle passed QA.
     */
    public function getPassedQa()
    {
        return $this->isPassed;

    }//end getPassedQa()


}//end class
