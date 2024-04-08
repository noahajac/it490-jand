<?php
/**
 * Represents a bundle type.
 *
 * @package JAND\Common\Deploy\BundleType
 */

namespace JAND\Common\Deploy;

/**
 * A bundle type.
 */
class BundleType
{

    /**
     * Directories to copy.
     *
     * @var string[] $directories Directories to copy.
     */
    private array $directories;

    /**
     * Services to restart.
     *
     * @var string[] $services Services to restart.
     */
    private array $services;

    /**
     * Scripts to run.
     *
     * @var string[] $scripts Scripts to run.
     */
    private array $scripts;

    /**
     * Bundle target.
     *
     * @var Target $target Target.
     */
    private Target $target;

    /**
     * Bundle name.
     *
     * @var string $name Bundle name.
     */
    private string $name;


    /**
     * Creates a bundle type.
     *
     * @param string   $name        Bundle name.
     * @param string[] $directories Directories to copy.
     * @param string[] $services    Services to restart.
     * @param Script[] $scripts     Scripts to run.
     * @param Target   $target      Bundle target.
     */
    public function __construct(
        string $name,
        array $directories,
        array $services,
        array $scripts,
        Target $target
    ) {
        $this->name        = $name;
        $this->directories = $directories;
        $this->services    = $services;
        $this->scripts     = $scripts;
        $this->target      = $target;

    }//end __construct()


    /**
     * Gets bundle name.
     *
     * @return string Bundle name.
     */
    public function getName()
    {
        return $this->name;

    }//end getName()


    /**
     * Gets directories to copy.
     *
     * @return string[] Directories to copy.
     */
    public function getDirectories()
    {
        return $this->directories;

    }//end getDirectories()


    /**
     * Gets services to restart.
     *
     * @return string[] Services to restart.
     */
    public function getServices()
    {
        return $this->services;

    }//end getServices()


    /**
     * Gets target.
     *
     * @return Target Bundle target.
     */
    public function getTarget()
    {
        return $this->target;

    }//end getTarget()


    /**
     * Gets scripts to run.
     *
     * @return Script[] Scripts to run.
     */
    public function getScripts()
    {
        return $this->scripts;

    }//end getScripts()


}//end class
