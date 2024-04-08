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
        } else if ($argv[1] === 'createbundle') {
            return Responders\CreateNewBundleResponder::respondToRequest($argv);
        } else if ($argv[1] === 'qapushbundle') {
            return Responders\QaPushBundleResponder::respondToRequest($argv);
        } else {
            return 'Please enter command getbundletypes, createbundle, or qapushbundle.'.PHP_EOL;
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
