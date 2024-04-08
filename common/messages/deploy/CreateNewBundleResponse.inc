<?php
/**
 * Contains response when creating a new bundle.
 *
 * @package JAND\Common\Messages\Deploy\CreateNewBundleResponse
 */

namespace JAND\Common\Messages\Deploy;

/**
 * A response when creating a new bundle.
 */
class CreateNewBundleResponse
{

    /**
     * Bundle version.
     *
     * @var integer $version Bundle version.
     */
    private int $version;


    /**
     * Creates a new bundle response.
     *
     * @param integer $version Bundle version.
     */
    public function __construct(int $version)
    {
        $this->version = $version;

    }//end __construct()


    /**
     * Gets the bundle version.
     *
     * @return integer Bundle version.
     */
    public function getVersion()
    {
        return $this->version;

    }//end getVersion()


}//end class
