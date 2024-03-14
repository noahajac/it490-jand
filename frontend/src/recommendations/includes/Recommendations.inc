<?php
/**
 * Contains frontend recommendations page.
 *
 * @package JAND\Frontend\Recommendations\Includes\Recommendations
 */

namespace JAND\Frontend\Recommendations\Includes;

/**
 * Frontend recommendations page.
 */
abstract class Recommendations
{


    /**
     * Echoes recommendations page.
     *
     * @return void
     */
    public static function echoRecommendations()
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
        <h1>Recommendations</h1>
        
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
    </body>

    </html>
        <?php

    }//end echoRecommendations()


}//end class