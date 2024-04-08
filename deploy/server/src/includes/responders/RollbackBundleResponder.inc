<?php
/**
 * Contains the responder for a bundle rollback.
 *
 * @package JAND\DeployServer\Includes\Responders\RollbackBundleResponder
 */

namespace JAND\DeployServer\Includes\Responders;

use JAND\Common\Deploy\Status;
use JAND\Common\Messages\Deploy\InstallBundleRequest;
use JAND\Common\Messages\Deploy\RollbackBundleRequest;
use JAND\Common\Messages\Deploy\RollbackBundleResponse;
use JAND\DeployServer\Includes\RabbitClientManager;

/**
 * Responds to rollback bundle requests.
 */
abstract class RollbackBundleResponder
{


    /**
     * Responds to rollback requests.
     *
     * @param RollbackBundleRequest $request Request.
     * @param \PDO                  $pdo     DB PDO.
     *
     * @return RollbackBundleResponse Response to request.
     */
    public static function respondToRequest(RollbackBundleRequest $request, \PDO $pdo)
    {
        $checkBundleStmt = $pdo->prepare(
            'SELECT * FROM bundles WHERE bundle_name=:bundleName AND 
status=:status ORDER BY version_number DESC'
        );
        $checkBundleStmt->execute(
            [
                'bundleName' => $request->getType()->getName(),
                'status'     => Status::Passed->value,
            ]
        );
        $checkBundleResults = $checkBundleStmt->fetch();
        $checkBundleStmt->closeCursor();

        if (empty($checkBundleResults)) {
            return new RollbackBundleResponse(false);
        }

        $target = $request->getTarget();

        $requestToInstall = new InstallBundleRequest($request->getType(), $checkBundleResults['version_number']);
        $requestToInstall->sendRequest(
            RabbitClientManager::getInstallerClient(),
            $target->value.'.'.$request->getType()->getTarget()->value
        );

        return new RollbackBundleResponse(true);

    }//end respondToRequest()


}//end class
