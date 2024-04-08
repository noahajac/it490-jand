<?php
/**
 * Contains main deploy client logic.
 *
 * @package JAND\DeployClient\Includes\DeployClient
 */

namespace JAND\DeployClient\Includes;

/**
 * Sends requests to deploy server.
 */
class DeployClient
{


    /**
     * Requests from the user get processed here.
     *
     * @param string[] $argv CLI arguments.
     *
     * @return mixed What to print to user.
     */
    private static function requestProcessor(array $argv)
    {
        if ($argv[1] === 'types') {
            return Responders\GetBundleTypesResponder::respondToRequest();
        } else if ($argv[1] === 'create') {
            return Responders\CreateNewBundleResponder::respondToRequest($argv);
        } else if ($argv[1] === 'push') {
            return Responders\PushBundleResponder::respondToRequest($argv);
        } else if ($argv[1] === 'list') {
            return Responders\GetBundlesResponder::respondToRequest($argv);
        } else if ($argv[1] === 'rollback') {
            return Responders\RollbackBundleResponder::respondToRequest($argv);
        } else if ($argv[1] === 'set') {
            return Responders\SetBundleStatusResponder::respondToRequest($argv);
        } else {
            $helpStr  = 'Available commands:'.PHP_EOL;
            $helpStr .= 'types'.PHP_EOL;
            $helpStr .= 'create   <NAME>'.PHP_EOL;
            $helpStr .= 'push     <NAME> <VERSION> (qa|prod)'.PHP_EOL;
            $helpStr .= 'list'.PHP_EOL;
            $helpStr .= 'rollback <NAME> (qa|prod)'.PHP_EOL;
            $helpStr .= 'set      <NAME> <VERSION> (pass|fail)'.PHP_EOL;
            return $helpStr;
        }//end if

    }//end requestProcessor()


    /**
     * Sends CLI arguments to request processor and prints output.
     *
     * @param string[] $argv CLI arguments.
     *
     * @return void
     */
    public static function start(array $argv)
    {
        echo static::requestProcessor($argv);

    }//end start()


}//end class
