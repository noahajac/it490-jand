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
     * @param \PDO                $pdo     DB PDO.
     *
     * @return QaPushBundleResponse Response to request.
     */
    public static function respondToRequest(QaPushBundleRequest $request, \PDO $pdo)
    {
        $checkBundleStmt = $pdo->prepare('SELECT * FROM bundles WHERE bundle_name=:bundleName AND version_number=:versionNumber');
        $checkBundleStmt->execute(
            [
                'bundleName'    => $request->getType()->getName(),
                'versionNumber' => $request->getVersion(),
            ]
        );
        $checkBundleResults = $checkBundleStmt->fetch();
        $checkBundleStmt->closeCursor();
        if (empty($checkBundleResults)) {
            return new QaPushBundleResponse(false);
        }

        $target = $request->getType()->getTarget();

        $requestToInstall = new InstallBundleRequest($request->getType(), $request->getVersion());
        $requestToInstall->sendRequest(RabbitClientManager::getInstallerClient(), 'qa.'.$target->value);

        return new QaPushBundleResponse(true);

    }//end respondToRequest()


}//end class
