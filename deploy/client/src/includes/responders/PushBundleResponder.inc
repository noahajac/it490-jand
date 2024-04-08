<?php
/**
 * Contains the responder for a push bundle command.
 *
 * @package JAND\DeployClient\Includes\Responders\PushBundleResponder
 */

namespace JAND\DeployClient\Includes\Responders;

use JAND\Common\Messages\Deploy\ProdPushBundleRequest;
use JAND\Common\Messages\Deploy\QaPushBundleRequest;
use JAND\Common\Messages\Deploy\QaPushBundleResponse;
use JAND\DeployClient\Includes\RabbitClientManager;

/**
 * Responds to push bundle commands.
 */
abstract class PushBundleResponder
{


    /**
     * Responds to a QA push bundle requests.
     *
     * @param array $argv CLI args.
     *
     * @return string Response to request.
     */
    public static function respondToRequest(array $argv)
    {
        $types         = GetBundleTypesResponder::respondToRequest(true);
        $bundleName    = $argv[2];
        $bundleVersion = $argv[3];

        $pushTarget = $argv[4];

        if ($pushTarget !== 'qa' && $pushTarget !== 'prod') {
            return 'Invalid target.'.PHP_EOL;
        }

        foreach ($types as &$type) {
            if ($type->getName() === $bundleName) {
                if ($pushTarget === 'qa') {
                    $request = new QaPushBundleRequest($type, $bundleVersion);
                    /**
                     * Response from server.
                     *
                     * @var QaPushBundleResponse $response Response from server.
                     */
                    $response = $request->sendRequest(RabbitClientManager::getClient());
                    if ($response->getIsBundle()) {
                        return 'Installed to QA bundle version '.$bundleVersion.'.'.PHP_EOL;
                    } else {
                        return 'Not a valid bundle.'.PHP_EOL;
                    }
                } else {
                    $request = new ProdPushBundleRequest($type, $bundleVersion);
                    /**
                     * Response from server.
                     *
                     * @var ProdPushBundleResponse $response Response from server.
                     */
                    $response = $request->sendRequest(RabbitClientManager::getClient());
                    if ($response->getIsBundle() && $response->getPassedQa()) {
                        return 'Installed to prod bundle version '.$bundleVersion.'.'.PHP_EOL;
                    } else if (!$response->getIsBundle()) {
                        return 'Not a valid bundle.'.PHP_EOL;
                    } else {
                        return 'Bundle did not pass QA.'.PHP_EOL;
                    }
                }//end if
            }//end if
        }//end foreach

        return 'Bundle name not found.'.PHP_EOL;

    }//end respondToRequest()


}//end class
