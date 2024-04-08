<?php
/**
 * Contains the responder for a rollback bundle command.
 *
 * @package JAND\DeployClient\Includes\Responders\RollbackBundleResponder
 */

namespace JAND\DeployClient\Includes\Responders;

use JAND\Common\Deploy\RollbackTarget;
use JAND\Common\Messages\Deploy\RollbackBundleResponse;
use JAND\Common\Messages\Deploy\RollbackBundleRequest;
use JAND\DeployClient\Includes\RabbitClientManager;

/**
 * Responds to rollback bundle commands.
 */
abstract class RollbackBundleResponder
{


    /**
     * Responds to a rollback bundle requests.
     *
     * @param array $argv CLI args.
     *
     * @return string Response to request.
     */
    public static function respondToRequest(array $argv)
    {
        $types          = GetBundleTypesResponder::respondToRequest(true);
        $providedType   = $argv[2];
        $providedTarget = $argv[3];

        $target = RollbackTarget::tryFrom($providedTarget);
        if ($target === null) {
            return 'Invalid rollback target.'.PHP_EOL;
        }

        foreach ($types as &$type) {
            if ($type->getName() === $providedType) {
                $request = new RollbackBundleRequest($type, $target);
                /**
                 * Response from server.
                 *
                 * @var RollbackBundleResponse $response Response from server.
                 */
                $response = $request->sendRequest(RabbitClientManager::getClient());
                if ($response->getIsBundle()) {
                    return 'Succesfully rolled back.'.PHP_EOL;
                } else {
                    return 'No passed bundle to rollback to.'.PHP_EOL;
                }
            }
        }

        return 'Bundle name not found.'.PHP_EOL;

    }//end respondToRequest()


}//end class
