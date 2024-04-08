<?php
/**
 * Contains the responder for a QA push bundle request.
 *
 * @package JAND\DeployServer\Includes\Responders\QaPushBundleResponder
 */

namespace JAND\DeployServer\Includes\Responders;

use JAND\Common\Messages\Deploy\InstallBundleRequest;
use JAND\Common\Messages\Deploy\QaPushBundleRequest;
use JAND\Common\Messages\Deploy\QaPushBundleResponse;
use JAND\DeployServer\Includes\RabbitClientManager;

/**
 * Responds to QA push bundle requests.
 */
abstract class QaPushBundleResponder
{


    /**
     * Responds to QA push bundle requests.
     *
     * @param QaPushBundleRequest $request Request.
     *
     * @return QaPushBundleResponse Response to request.
     */
    public static function respondToRequest(QaPushBundleRequest $request)
    {
        $target = $request->getType()->getTarget();

        $requestToInstall = new InstallBundleRequest($request->getType(), $request->getVersion());
        $requestToInstall->sendRequest(RabbitClientManager::getInstallerClient(), 'qa.'.$target->value);

        return new QaPushBundleResponse(true);

    }//end respondToRequest()


}//end class
