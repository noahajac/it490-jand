<?php
/**
 * Contains the responder for a set bundle status request.
 *
 * @package JAND\DeployServer\Includes\Responders\SetBundleStatusResponder
 */

namespace JAND\DeployServer\Includes\Responders;

use JAND\Common\Messages\Deploy\SetBundleStatusRequest;
use JAND\Common\Messages\Deploy\SetBundleStatusResponse;
use JAND\DeployServer\Includes\RabbitClientManager;

/**
 * Responds to set bundle status requests.
 */
abstract class SetBundleStatusResponder
{


    /**
     * Responds to a set bundle status request.
     *
     * @param SetBundleStatusRequest $request Request.
     * @param \PDO                   $pdo     DB PDO.
     *
     * @return SetBundleStatusResponse Response to request.
     */
    public static function respondToRequest(SetBundleStatusRequest $request, \PDO $pdo)
    {
        $updateStatusStmt = $pdo->prepare(
            'UPDATE bundles SET status=:status 
WHERE bundle_name=:bundleName AND version_number=:versionNumber'
        );
        $updateStatusStmt->execute(
            [
                'bundleName'    => $request->getBundle()->getType()->getName(),
                'versionNumber' => $request->getBundle()->getVersion(),
                'status'        => $request->getBundle()->getStatus()->value,
            ]
        );
        if ($updateStatusStmt->rowCount() > 0) {
            $found = true;
        } else {
            $found = false;
        }

        return new SetBundleStatusResponse($found);

    }//end respondToRequest()


}//end class
