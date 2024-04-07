<?php
/**
 * Contains the responder for a get bundle types request.
 *
 * @package JAND\DeployServer\Includes\Responders\GetBundleTypesResponder
 */

namespace JAND\DeployServer\Includes\Responders;

use JAND\Common\Deploy\BundleType;
use JAND\Common\Deploy\Target;

/**
 * Responds to get bundle types requests.
 */
abstract class GetBundleTypesResponder
{


    /**
     * Responds to a get bundle types requests.
     *
     * @return \JAND\Common\Messages\Deploy\GetBundleTypesResponse Response to request.
     */
    public static function respondToRequest()
    {
        /**
         * Bundle types.
         *
         * @var BundleType[] $bundleTypes Bundle types.
         */
        $bundleTypes = [];

        $bundleIniValues = parse_ini_file(__DIR__.'/../bundles.ini', true);

        foreach ($bundleIniValues as $name => &$bundleConfig) {
            if (isset($bundleConfig['DIRECTORIES'])) {
                $directories = $bundleConfig['DIRECTORIES'];
            } else {
                $directories = [];
            }

            if (isset($bundleConfig['SERVICES'])) {
                $services = $bundleConfig['SERVICES'];
            } else {
                $services = [];
            }

            if (isset($bundleConfig['SCRIPTS'])) {
                $scripts = $bundleConfig['SCRIPTS'];
            } else {
                $scripts = [];
            }

            $target = Target::tryFrom($bundleConfig['TARGET']);

            array_push(
                $bundleTypes,
                new BundleType(
                    $name,
                    $directories,
                    $services,
                    $scripts,
                    $target
                )
            );
        }//end foreach

        return new \JAND\Common\Messages\Deploy\GetBundleTypesResponse($bundleTypes);

    }//end respondToRequest()


}//end class
