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
        if ($argv[1] === 'getbundletypes') {
            return Responders\GetBundleTypesResponder::respondToRequest();
        } else {
            return 'Please enter command.'.PHP_EOL;
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
