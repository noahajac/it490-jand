<?php
/**
 * Represents a bundle.
 *
 * @package JAND\Common\Deploy\Bundle
 */

namespace JAND\Common\Deploy;

/**
 * A bundle.
 */
class Bundle
{

    /**
     * Bundle type.
     *
     * @var BundleType $type Bundle type.
     */
    private BundleType $type;

    /**
     * Bundle status.
     *
     * @var Status $status Bundle status.
     */
    private Status $status;

    /**
     * Bundle version.
     *
     * @var integer $version Bundle version.
     */
    private int $version;


    /**
     * Creates a bundle.
     *
     * @param BundleType $type    Bundle type.
     * @param Status     $status  Bundle status.
     * @param integer    $version Bundle version.
     */
    public function __construct(
        BundleType $type,
        Status $status,
        int $version,
    ) {
        $this->type    = $type;
        $this->status  = $status;
        $this->version = $version;

    }//end __construct()


    /**
     * Get bundle type.
     *
     * @return BundleType Bundle type.
     */
    public function getType()
    {
        return $this->type;

    }//end getType()


    /**
     * Get bundle status.
     *
     * @return Status Bundle status.
     */
    public function getStatus()
    {
        return $this->status;

    }//end getStatus()


    /**
     * Get bundle version.
     *
     * @return integer Bundle version.
     */
    public function getVersion()
    {
        return $this->version;

    }//end getVersion()


}//end class
