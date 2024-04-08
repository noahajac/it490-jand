<?php
/**
 * Contains the responder for a create new bundle command.
 *
 * @package JAND\DeployClient\Includes\Responders\CreateNewBundleResponder
 */

namespace JAND\DeployClient\Includes\Responders;

use JAND\Common\Deploy\BundleType;
use JAND\Common\Messages\Deploy\CreateNewBundleRequest;
use JAND\Common\Messages\Deploy\GetBundleTypesRequest;
use JAND\Common\Messages\Deploy\GetBundleTypesResponse;
use JAND\DeployClient\Includes\RabbitClientManager;

/**
 * Responds to create new bundle commands.
 */
abstract class CreateNewBundleResponder
{


    /**
     * Responds to a get bundle types requests.
     *
     * @param array $argv CLI args.
     *
     * @return string Response to request.
     */
    public static function respondToRequest(array $argv)
    {
        $types        = GetBundleTypesResponder::respondToRequest(true);
        $providedType = $argv[2];

        foreach ($types as &$type) {
            if ($type->getName() === $providedType) {
                $request  = new CreateNewBundleRequest($type);
                $response = $request->sendRequest(RabbitClientManager::getClient());
                return 'Created bundle version '.$response->getVersion().'.'.PHP_EOL;
            }
        }

        return 'Bundle name not found.'.PHP_EOL;

    }//end respondToRequest()


}//end class
