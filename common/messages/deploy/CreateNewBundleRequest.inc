<?php
/**
 * Contains message to create a new bundle.
 *
 * @package JAND\Common\Messages\Deploy\CreateNewBundleRequest
 */

namespace JAND\Common\Messages\Deploy;

use JAND\Common\Deploy\BundleType;

/**
 * A request to create a new bundle.
 */
class CreateNewBundleRequest extends \JAND\Common\Messages\Request
{

    /**
     * Bundle version.
     * Not sent on requests from client.
     *
     * @var ?int $version Bundle version.
     */
    private ?int $version;

    /**
     * Bundle type.
     *
     * @var BundleType $type Bundle type.
     */
    private BundleType $type;


    /**
     * Creates a new bundle request.
     *
     * @param BundleType $type    Type of bundle.
     * @param integer    $version Bundle version.
     */
    public function __construct(BundleType $type, ?int $version=null)
    {
        $this->type    = $type;
        $this->version = $version;

    }//end __construct()


    /**
     * Sets the version for the bundle to create.
     *
     * @param integer $version Version of bundle.
     *
     * @return void
     */
    public function setVersion(int $version)
    {
        $this->version = $version;

    }//end setVersion()


    /**
     * Gets the bundle version.
     *
     * @return integer Bundle version.
     */
    public function getVersion()
    {
        return $this->version;

    }//end getVersion()


    /**
     * Gets the bundle type.
     *
     * @return BundleType Bundle type.
     */
    public function getType()
    {
        return $this->type;

    }//end getType()


}//end class
