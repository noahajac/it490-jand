<?php
/**
 * Contains the responder for a get bundle types command.
 *
 * @package JAND\DeployClient\Includes\Responders\GetBundleTypesResponder
 */

namespace JAND\DeployClient\Includes\Responders;

use JAND\Common\Deploy\BundleType;
use JAND\Common\Messages\Deploy\GetBundleTypesRequest;
use JAND\Common\Messages\Deploy\GetBundleTypesResponse;
use JAND\DeployClient\Includes\RabbitClientManager;

/**
 * Responds to get bundle types command.
 */
abstract class GetBundleTypesResponder
{


    /**
     * Responds to a get bundle types requests.
     *
     * @return string Response to request.
     */
    public static function respondToRequest()
    {
        $request = new GetBundleTypesRequest();

        /**
         * Bundle types response.
         *
         * @var GetBundleTypesResponse $bundleTypesResponse Bundle types response.
         */
        $bundleTypesResponse = $request->sendRequest(RabbitClientManager::getClient());

        $bundleTypes = $bundleTypesResponse->getResults();

        if (count($bundleTypes) < 1) {
            return 'No types found.'.PHP_EOL;
        } else {
            $response = '';
            foreach ($bundleTypes as &$bundleType) {
                $response .= $bundleType->getName().PHP_EOL;
            }

            return $response;
        }

    }//end respondToRequest()


}//end class
