<?php
/**
 * Contains the responder for a create new bundle request.
 *
 * @package JAND\DeployServer\Includes\Responders\CreateNewBundleResponder
 */

namespace JAND\DeployServer\Includes\Responders;

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
     * @param \PDO                   $pdo     DB PDO.
     *
     * @return CreateNewBundleResponse Response to request.
     */
    public static function respondToRequest(CreateNewBundleRequest $request, \PDO $pdo)
    {
        $getLastStmt = $pdo->prepare(
            'SELECT * FROM bundles 
WHERE bundle_name=:bundleName ORDER BY version_number DESC'
        );
        $getLastStmt->execute(
            [
                'bundleName' => $request->getType()->getName(),
            ]
        );
        $lastBundle = $getLastStmt->fetch();
        $getLastStmt->closeCursor();

        if (empty($lastBundle)) {
            $nextVersion = 1;
        } else {
            echo $lastBundle['version_number'];
            $nextVersion = ($lastBundle['version_number'] + 1);
        }

        $createBundleStmt = $pdo->prepare(
            'INSERT INTO bundles VALUES 
(:bundleName, :versionNumber, 0)'
        );
        $createBundleStmt->execute(
            [
                'bundleName'    => $request->getType()->getName(),
                'versionNumber' => $nextVersion,
            ]
        );
        $createBundleStmt->closeCursor();

        $target = $request->getType()->getTarget();

        $request->setVersion($nextVersion);
        $request->sendRequest(RabbitClientManager::getBundlerClient(), $target->value);

        return new CreateNewBundleResponse($nextVersion);

    }//end respondToRequest()


}//end class
