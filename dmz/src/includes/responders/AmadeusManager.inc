<?php
/**
 * Manages auth for Amadeus API use.
 *
 * @package JAND\Dmz\Includes\Responders\AmadeusManager
 */

namespace JAND\Dmz\Includes\Responders;

use DateTime;

/**
 * Manages Amadeus API use.
 */
abstract class AmadeusManager
{

    /**
     * Whether config was already pulled from ini.
     *
     * @var boolean $configPulled If config was already pulled.
     */
    private static bool $configPulled = false;

    /**
     * Base URL for API calls.
     *
     * @var string $apiUrl URL for API calls.
     */
    private static string $apiUrl;

    /**
     * Client ID for auth.
     *
     * @var string $clientId Client ID.
     */
    private static string $clientId;

    /**
     * Client secret for auth.
     *
     * @var string $clientSecret Client secret.
     */
    private static string $clientSecret;

    /**
     * Bearer auth header.
     *
     * @var string $authHeader Bearer auth header.
     */
    private static string $authHeader;

    /**
     * When the current header would expire.
     *
     * @var integer $headerExpires When the current header expires.
     */
    private static int $headerExpires;


    /**
     * Pulls the config from ini if not done already.
     *
     * @return void
     */
    private static function getConfig()
    {
        if (!static::$configPulled) {
            $configFile           = parse_ini_file(__DIR__.'/amadeus.ini');
            static::$apiUrl       = $configFile['API_URL'];
            static::$clientId     = $configFile['CLIENT_ID'];
            static::$clientSecret = $configFile['CLIENT_SECRET'];
            static::$configPulled = true;
        }

    }//end getConfig()


    /**
     * Gets the API url.
     *
     * @return string API url.
     */
    public static function getApiUrl()
    {
        static::getConfig();
        return static::$apiUrl;

    }//end getApiUrl()


    /**
     * Gets the client ID.
     *
     * @return string Client ID.
     */
    private static function getClientId()
    {
        static::getConfig();
        return static::$clientId;

    }//end getClientId()


    /**
     * Gets the client secret.
     *
     * @return string Client secret.
     */
    private static function getClientSecret()
    {
        static::getConfig();
        return static::$clientSecret;

    }//end getClientSecret()


    /**
     * Gets the authorization header.
     * Will call API for new one if not set or if it expires
     * within 30 seconds.
     *
     * @return string Bearer auth header.
     */
    public static function getAuthorizationHeader()
    {
        if (!isset(static::$authHeader) || (static::$headerExpires - 30) < time()) {
            $curl = curl_init(static::getApiUrl().'/v1/security/oauth2/token');
            curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
            curl_setopt(
                $curl,
                CURLOPT_HTTPHEADER,
                ['Content-Type: application/x-www-form-urlencoded']
            );
            $postParams = http_build_query(
                [
                    'grant_type'    => 'client_credentials',
                    'client_id'     => static::getClientId(),
                    'client_secret' => static::getClientSecret(),
                ]
            );
            curl_setopt($curl, CURLOPT_POST, true);
            curl_setopt($curl, CURLOPT_POSTFIELDS, $postParams);
            $response = json_decode(curl_exec($curl));
            curl_close($curl);

            // phpcs:ignore Squiz.NamingConventions.ValidVariableName.MemberNotCamelCaps
            static::$authHeader = 'Authorization: '.$response->token_type.' '.$response->access_token;
            // phpcs:ignore Squiz.NamingConventions.ValidVariableName.MemberNotCamelCaps
            static::$headerExpires = (time() + $response->expires_in);
        }//end if

        return static::$authHeader;

    }//end getAuthorizationHeader()


}//end class
