<?php
/**
 * Contains message to rollback bundle.
 *
 * @package JAND\Common\Messages\Deploy\CreateNewBundleRequest
 */

namespace JAND\Common\Messages\Deploy;

use JAND\Common\Deploy\BundleType;
use JAND\Common\Deploy\RollbackTarget;

/**
 * A request to rollback bundle.
 */
class RollbackBundleRequest extends \JAND\Common\Messages\Request
{

    /**
     * Rollback target.
     *
     * @var RollbackTarget $target Rollback target.
     */
    private RollbackTarget $target;

    /**
     * Bundle type.
     *
     * @var BundleType $type Bundle type.
     */
    private BundleType $type;


    /**
     * Creates a new bundle request.
     *
     * @param BundleType     $type   Type of bundle.
     * @param RollbackTarget $target Rollback target.
     */
    public function __construct(BundleType $type, RollbackTarget $target)
    {
        $this->type   = $type;
        $this->target = $target;

    }//end __construct()


    /**
     * Gets the rollback target.
     *
     * @return RollbackTarget Rollback target.
     */
    public function getTarget()
    {
        return $this->target;

    }//end getTarget()


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
