<?php
/**
 * Contains the logout frontend page.
 *
 * @package JAND\Frontend\Logout\Includes\Logout
 */

namespace JAND\Frontend\Logout\Includes;

use JAND\Frontend\Includes\LogSender;

/**
 * Logout frontend page.
 */
abstract class Logout
{


    /**
     * Performs logout and echoes HTML on error.
     *
     * @return void
     */
    public static function echoLogout()
    {
        LogSender::sendLog('Received a logout request.');

        // Technically this can error, but it shouldn't ever happen.
        if (\JAND\Frontend\Includes\SessionManager::logout()) {
            header('Location: /landing');
            exit();
        }
        ?>

    <!DOCTYPE html>
    <html lang="en">

    <head>
        <?php echo \JAND\Frontend\Includes\Elements\Head::echoHead(); ?>
    </head>

    <body>
        <?php echo \JAND\Frontend\Includes\Elements\Nav::echoNav(); ?>
      <main>
        <h1 class="error">Error logging out! Please contact site administrator.</h1>
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
    </body>

    </html>

        <?php

    }//end echoLogout()


}//end class
