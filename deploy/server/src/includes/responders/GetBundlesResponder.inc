<?php
/**
 * Contains the responder for a get bundles request.
 *
 * @package JAND\DeployServer\Includes\Responders\GetBundlesResponder
 */

namespace JAND\DeployServer\Includes\Responders;

use JAND\Common\Deploy\Bundle;
use JAND\Common\Deploy\Status;

/**
 * Responds to get bundles requests.
 */
abstract class GetBundlesResponder
{


    /**
     * Responds to a get bundles requests.
     *
     * @param \PDO $pdo DB PDO.
     *
     * @return \JAND\Common\Messages\Deploy\GetBundlesResponse Response to request.
     */
    public static function respondToRequest(\PDO $pdo)
    {
        $bundleTypes = GetBundleTypesResponder::respondToRequest()->getResults();

        /**
         * Bundles.
         *
         * @var Bundle[] $bundles Bundles.
         */
        $bundles = [];

        $getBundlesStmt = $pdo->prepare('SELECT * FROM bundles');
        $getBundlesStmt->execute();
        $getBundlesResults = $getBundlesStmt->fetchAll();
        $getBundlesStmt->closeCursor();

        foreach ($getBundlesResults as &$result) {
            $status = Status::tryFrom($result['status']);

            foreach ($bundleTypes as &$testType) {
                if ($testType->getName() === $result['bundle_name']) {
                    array_push($bundles, new Bundle($testType, $status, $result['version_number']));
                    break;
                }
            }
        }

        return new \JAND\Common\Messages\Deploy\GetBundlesResponse($bundles);

    }//end respondToRequest()


}//end class
