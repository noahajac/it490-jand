<?php
/**
 * Contains message to set bundle status.
 *
 * @package JAND\Common\Messages\Deploy\SetBundleStatusRequest
 */

namespace JAND\Common\Messages\Deploy;

use JAND\Common\Deploy\Bundle;

/**
 * A request to set bundle status.
 */
class SetBundleStatusRequest extends \JAND\Common\Messages\Request
{

    /**
     * Bundle with status.
     *
     * @var Bundle $bundle Bundle.
     */
    private Bundle $bundle;


    /**
     * Creates a new bundle status set request.
     *
     * @param Bundle $bundle Bundle.
     */
    public function __construct(Bundle $bundle)
    {
        $this->bundle = $bundle;

    }//end __construct()


    /**
     * Gets the bundle.
     *
     * @return Bundle Bundle.
     */
    public function getBundle()
    {
        return $this->bundle;

    }//end getBundle()


}//end class
