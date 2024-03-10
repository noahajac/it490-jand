<?php
/**
 * Contains frontend main landing page.
 *
 * @package JAND\Frontend\Landing\Includes\Landing
 */

namespace JAND\Frontend\Landing\Includes;

/**
 * Main landing page.
 */
abstract class Landing
{


    /**
     * Echoes main landing page.
     *
     * @return void
     */
    public static function echoLanding()
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
        <h1>Welcome to JAND Travel</h1>
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
    </body>

    </html>
        <?php

    }//end echoLanding()


}//end class
