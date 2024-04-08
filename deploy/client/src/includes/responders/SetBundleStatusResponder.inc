<?php
/**
 * Contains the responder for a set bundle status command.
 *
 * @package JAND\DeployClient\Includes\Responders\SetBundleStatusResponder
 */

namespace JAND\DeployClient\Includes\Responders;

use JAND\Common\Deploy\Bundle;
use JAND\Common\Deploy\Status;
use JAND\Common\Messages\Deploy\SetBundleStatusRequest;
use JAND\Common\Messages\Deploy\SetBundleStatusResponse;
use JAND\DeployClient\Includes\RabbitClientManager;

/**
 * Responds to set bundle status commands.
 */
abstract class SetBundleStatusResponder
{


    /**
     * Responds to a set bundle status request.
     *
     * @param array $argv CLI args.
     *
     * @return string Response to request.
     */
    public static function respondToRequest(array $argv)
    {
        $types          = GetBundleTypesResponder::respondToRequest(true);
        $providedType   = $argv[2];
        $version        = $argv[3];
        $providedStatus = $argv[4];

        if ($providedStatus === 'pass') {
            $status = Status::Passed;
        } else if ($providedStatus === 'fail') {
            $status = Status::Failed;
        } else {
            return 'Invalid status.';
        }

        foreach ($types as &$type) {
            if ($type->getName() === $providedType) {
                $request = new SetBundleStatusRequest(new Bundle($type, $status, $version));
                /**
                 * Response from server.
                 *
                 * @var SetBundleStatusResponse $response Response from server.
                 */
                $response = $request->sendRequest(RabbitClientManager::getClient());
                if ($response->getIsBundle()) {
                    return 'Succesfully set status.'.PHP_EOL;
                } else {
                    return 'Bundle not found.'.PHP_EOL;
                }
            }
        }

        return 'Bundle name not found.'.PHP_EOL;

    }//end respondToRequest()


}//end class
