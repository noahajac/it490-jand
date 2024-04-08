<?php
/**
 * Contains the responder for a QA push bundle command.
 *
 * @package JAND\DeployClient\Includes\Responders\QaPushBundleResponder
 */

namespace JAND\DeployClient\Includes\Responders;

use JAND\Common\Messages\Deploy\QaPushBundleRequest;
use JAND\DeployClient\Includes\RabbitClientManager;

/**
 * Responds to QA push bundle commands.
 */
abstract class QaPushBundleResponder
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

        foreach ($types as &$type) {
            if ($type->getName() === $bundleName) {
                $request = new QaPushBundleRequest($type, $bundleVersion);
                $request->sendRequest(RabbitClientManager::getClient());
                return 'Installed to QA bundle version '.$bundleVersion.'.'.PHP_EOL;
            }
        }

        return 'Bundle name not found.'.PHP_EOL;

    }//end respondToRequest()


}//end class
