<?php
/**
 * Contains the responder for a prod push bundle request.
 *
 * @package JAND\DeployServer\Includes\Responders\ProdPushBundleResponder
 */

namespace JAND\DeployServer\Includes\Responders;

use JAND\Common\Deploy\Status;
use JAND\Common\Messages\Deploy\InstallBundleRequest;
use JAND\Common\Messages\Deploy\ProdPushBundleRequest;
use JAND\Common\Messages\Deploy\ProdPushBundleResponse;
use JAND\DeployServer\Includes\RabbitClientManager;

/**
 * Responds to prod push bundle requests.
 */
abstract class ProdPushBundleResponder
{


    /**
     * Responds to prod push bundle requests.
     *
     * @param ProdPushBundleRequest $request Request.
     * @param \PDO                  $pdo     DB PDO.
     *
     * @return ProdPushBundleResponse Response to request.
     */
    public static function respondToRequest(ProdPushBundleRequest $request, \PDO $pdo)
    {
        $checkBundleStmt = $pdo->prepare(
            'SELECT * FROM bundles WHERE bundle_name=:bundleName AND 
version_number=:versionNumber'
        );
        $checkBundleStmt->execute(
            [
                'bundleName'    => $request->getType()->getName(),
                'versionNumber' => $request->getVersion(),
            ]
        );
        $checkBundleResults = $checkBundleStmt->fetch();
        $checkBundleStmt->closeCursor();
        if (empty($checkBundleResults)) {
            return new ProdPushBundleResponse(false, false);
        } else if (Status::tryFrom($checkBundleResults['status']) !== Status::Passed) {
            return new ProdPushBundleResponse(true, false);
        }

        $target = $request->getType()->getTarget();

        $requestToInstall = new InstallBundleRequest($request->getType(), $request->getVersion());
        $requestToInstall->sendRequest(RabbitClientManager::getInstallerClient(), 'prod.'.$target->value);

        return new ProdPushBundleResponse(true, true);

    }//end respondToRequest()


}//end class
