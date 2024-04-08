<?php
/**
 * Contains the responder for a install bundle request.
 *
 * @package JAND\DeployInstaller\Includes\Responders\InstallBundleResponder
 */

namespace JAND\DeployInstaller\Includes\Responders;

use JAND\Common\Deploy\Script;
use JAND\Common\Messages\Deploy\InstallBundleRequest;
use JAND\Common\Messages\Deploy\InstallBundleResponse;
use PharData;

/**
 * Responds to install bundle requests.
 */
abstract class InstallBundleResponder
{


    /**
     * Responds to install bundle requests.
     *
     * @param InstallBundleRequest $request The request.
     *
     * @return InstallBundleResponse Response to request.
     */
    public static function respondToRequest(InstallBundleRequest $request)
    {
        $version     = $request->getVersion();
        $directories = $request->getType()->getDirectories();
        $services    = $request->getType()->getServices();
        $target      = $request->getType()->getTarget()->value;
        $name        = $request->getType()->getName();
        $scripts     = $request->getType()->getScripts();

        $buildDir       = '/tmp/jand-deploy-installer/'.$name.'-'.$version;
        $directoriesDir = $buildDir.'/directories';
        $scriptsDir     = $buildDir.'/scripts';

        if (!is_dir('/tmp/jand-deploy-installer')) {
            mkdir('/tmp/jand-deploy-installer', 0755);
        }

        shell_exec('scp /var/lib/jand/'.$name.'-'.$version.'.tar '.$buildDir.'.tar');

        mkdir($buildDir, 0755);

        $phar = new PharData($buildDir.'.tar');
        $phar->extractTo($buildDir);

        foreach ($directories as &$directory) {
            $fullPath = '/srv/'.$target.'/'.$directory;
            shell_exec('rm -rf '.$fullPath.'/{..?*,.[!.]*,*}');
            shell_exec('cp -RT '.$directoriesDir.'/'.$directory.' '.$fullPath);
        }

        foreach ($scripts as &$script) {
            if ($script === Script::Rabbitmq) {
                shell_exec('sudo /srv/jand-deploy-installer/scripts/restore-definitions '.$scriptsDir);
            }
        }

        shell_exec('rm -rf '.$buildDir);
        shell_exec('rm -rf '.$buildDir.'.tar');
        foreach ($services as &$service) {
            shell_exec('sudo systemctl restart '.$service.'.service');
        }

        return new InstallBundleResponse($version);

    }//end respondToRequest()


}//end class
