<?php
/**
 * Contains the responder for a create new bundle request.
 *
 * @package JAND\DeployServer\Includes\Responders\CreateNewBundleResponder
 */

namespace JAND\DeployServer\Includes\Responders;

use JAND\Common\Deploy\BundleType;
use JAND\Common\Deploy\Target;
use JAND\Common\Messages\Deploy\CreateNewBundleRequest;
use JAND\Common\Messages\Deploy\CreateNewBundleResponse;
use JAND\DeployServer\Includes\RabbitClientManager;

/**
 * Responds to create new bundle requests.
 */
abstract class CreateNewBundleResponder
{


    /**
     * Responds to a create new bundle request.
     *
     * @param CreateNewBundleRequest $request Request.
     *
     * @return CreateNewBundleResponse Response to request.
     */
    public static function respondToRequest(CreateNewBundleRequest $request)
    {
        $version = 1;

        $target = $request->getType()->getTarget();

        $request->setVersion($version);
        $request->sendRequest(RabbitClientManager::getBundlerClient(), $target->value);

        return new CreateNewBundleResponse($version);

    }//end respondToRequest()


}//end class
