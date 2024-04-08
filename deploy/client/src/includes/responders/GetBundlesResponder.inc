<?php
/**
 * Contains the responder for a get bundles command.
 *
 * @package JAND\DeployClient\Includes\Responders\GetBundlesResponder
 */

namespace JAND\DeployClient\Includes\Responders;

use JAND\Common\Messages\Deploy\GetBundlesRequest;
use JAND\Common\Messages\Deploy\GetBundlesResponse;
use JAND\DeployClient\Includes\RabbitClientManager;

/**
 * Responds to get bundles command.
 */
abstract class GetBundlesResponder
{


    /**
     * Responds to a get bundles requests.
     *
     * @return string Response to request.
     */
    public static function respondToRequest()
    {
        $request = new GetBundlesRequest();

        /**
         * Bundle types response.
         *
         * @var GetBundlesResponse $bundlesResponse Bundle types response.
         */
        $bundlesResponse = $request->sendRequest(RabbitClientManager::getClient());

        $bundles = $bundlesResponse->getResults();

        if (count($bundles) < 1) {
            return 'No bundles found.'.PHP_EOL;
        } else {
            $response = '';
            foreach ($bundles as &$bundle) {
                $name      = $bundle->getType()->getName();
                $version   = $bundle->getVersion();
                $status    = $bundle->getStatus()->name;
                $response .= $name.'   v'.$version.'   '.$status.PHP_EOL;
            }

            return $response;
        }

    }//end respondToRequest()


}//end class
