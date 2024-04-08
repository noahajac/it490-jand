<?php
/**
 * Contains the responder for a get bundle types request.
 *
 * @package JAND\DeployBundler\Includes\Responders\CreateNewBundleResponder
 */

namespace JAND\DeployBundler\Includes\Responders;

use JAND\Common\Deploy\Script;
use JAND\Common\Messages\Deploy\CreateNewBundleRequest;
use JAND\Common\Messages\Deploy\CreateNewBundleResponse;
use PharData;

/**
 * Responds to create new bundle requests.
 */
abstract class CreateNewBundleResponder
{


    /**
     * Responds to a create new bundle requests.
     *
     * @param CreateNewBundleRequest $request The request.
     *
     * @return \JAND\Common\Messages\Deploy\CreateNewBundleResponse Response to request.
     */
    public static function respondToRequest(CreateNewBundleRequest $request)
    {
        $version     = $request->getVersion();
        $directories = $request->getType()->getDirectories();
        $scripts     = $request->getType()->getScripts();
        $target      = $request->getType()->getTarget()->value;
        $name        = $request->getType()->getName();

        $buildDir       = '/tmp/jand-deploy-bundler/'.$name.'-'.$version;
        $directoriesDir = $buildDir.'/directories';
        $scriptsDir     = $buildDir.'/scripts';

        if (!is_dir('/tmp/jand-deploy-bundler')) {
            mkdir('/tmp/jand-deploy-bundler', 0755);
        }

        mkdir($buildDir, 0755);
        mkdir($directoriesDir, 0755);
        mkdir($scriptsDir, 0755);

        foreach ($directories as &$directory) {
            $fullPath = '/srv/'.$target.'/'.$directory;
            shell_exec('cp -RT '.$fullPath.' '.$directoriesDir.'/'.$directory);
        }

        foreach ($scripts as &$script) {
            if ($script === Script::Rabbitmq) {
                shell_exec('sudo /srv/jand-deploy-bundler/scripts/backup-definitions '.$scriptsDir);
            }
        }

        $phar = new PharData($buildDir.'.tar');
        $phar->buildFromDirectory($buildDir);

        shell_exec('scp '.$buildDir.'.tar /var/lib/jand/'.$name.'-'.$version.'.tar');

        shell_exec('rm -rf '.$buildDir);
        shell_exec('rm -rf '.$buildDir.'.tar');

        return new CreateNewBundleResponse($version);

    }//end respondToRequest()


}//end class
