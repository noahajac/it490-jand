<?php
/**
 * Contains frontend user preferences page.
 *
 * @package JAND\Frontend\UserPreferences\Includes\UserPreferences
 */

namespace JAND\Frontend\UserPreferences\Includes;

use JAND\Frontend\Includes\SessionManager;

/**
 * Frontend user preferences page.
 */
abstract class UserPreferences
{


    /**
     * Echoes user preferences page.
     *
     * @return void
     */
    private static function echoUserPreferences()
    {
        ?>

    <!DOCTYPE html>
    <html lang="en">

    <head>
        <?php echo \JAND\Frontend\Includes\Elements\Head::echoHead(); ?>
        <link rel="stylesheet" href="styles/user-preferences.css">
    </head>

    <body>
        <?php echo \JAND\Frontend\Includes\Elements\Nav::echoNav(); ?>
      <main>
        <h1>Set Your Travel Preferences</h1>
        <div class="preference-container">
        
        
            <form name="input-preference" id="input-preference" method="post">

                <h3>Destinations to Visit</h3>
        <div class="preference">
        <?php
        $request = new \JAND\Common\Messages\Frontend\GetPoiKeywordsRequest();
        /**
         * Keywords from DB.
         *
         * @var \JAND\Common\Messages\Frontend\GetPoiKeywordsResponse $keywordResponse Response.
         */
        $keywordResponse = $request->sendRequest(\JAND\Frontend\Includes\RabbitClientManager::getClient());

        $request = new \JAND\Common\Messages\Frontend\GetUserKeywordPrefRequest(
            SessionManager::getSession()->getSessionToken()
        );
            /**
             * Keywords from DB.
             *
             * @var \JAND\Common\Messages\Frontend\GetUserKeywordPrefResponse $userResponse Response.
             */
            $userResponse = $request->sendRequest(\JAND\Frontend\Includes\RabbitClientManager::getClient());

        foreach ($keywordResponse->getKeywords() as &$keyword) {
            $selected = false;
            if (in_array($keyword, $userResponse->getKeywords(), true)) {
                // User already selected this one.
                $selected = true;
            }
            ?>
                    <div class="preference">
                    <input id="<?= $keyword; ?>" name="<?= $keyword; ?>" type="checkbox" 
                <?php
                if ($selected) {
                    ?>
                        checked="true" 
                    <?php
                }
                ?>
                    >
                    <label for="<?= $keyword; ?>"><?= ucwords($keyword); ?></label>
                    </div>
                  <?php
        }//end foreach
        ?>
                <button type="submit">Save</button>
            </form>
        </div>
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
    </body>

    </html>
        <?php

    }//end echoUserPreferences()


    /**
     * Processes requests for user preferences page.
     *
     * @return void
     */
    public static function processUserPreferences()
    {
        $session = \JAND\Frontend\Includes\SessionManager::getSession();

        if (!$session) {
            http_response_code(401);
            exit();
        }

        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            $enabledKeywords = [];

            foreach ($_POST as $keyword => &$value) {
                array_push($enabledKeywords, $keyword);
            }

            $request = new \JAND\Common\Messages\Frontend\SetUserKeywordPrefRequest(
                $session->getSessionToken(),
                $enabledKeywords
            );
            $request->sendRequest(\JAND\Frontend\Includes\RabbitClientManager::getClient());
        }//end if

        static::echoUserPreferences();

    }//end processUserPreferences()


}//end class