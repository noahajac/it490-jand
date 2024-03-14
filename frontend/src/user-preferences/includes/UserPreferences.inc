<?php
/**
 * Contains frontend user preferences page.
 *
 * @package JAND\Frontend\UserPreferences\Includes\UserPreferences
 */

namespace JAND\Frontend\UserPreferences\Includes;

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
    public static function echoUserPreferences()
    {
        ?>

    <!DOCTYPE html>
    <html lang="en">

    <head>
        <?php echo \JAND\Frontend\Includes\Elements\Head::echoHead(); ?>
    </head>

    <body>
        <?php echo \JAND\Frontend\Includes\Elements\Nav::echoNav(); ?>
      <main>
        <h1>User Preferences</h1>
        
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
    </body>

    </html>
        <?php

    }//end echoUserPreferences()


}//end class