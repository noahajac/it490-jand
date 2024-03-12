<?php
/**
 * Contains frontend user trips page.
 *
 * @package JAND\Frontend\UserTrips\Includes\UserTrips
 */

namespace JAND\Frontend\UserTrips\Includes;

/**
 * User trips page.
 */
abstract class UserTrips
{


    /**
     * Echoes user trips page.
     *
     * @return void
     */
    public static function echoUserTrips()
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
        <form>
            <input type="text" id="destination" name="destination">
        </form>
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
        <script src="/scripts/airport-autocomplete.js"></script>
        <script src="./scripts/register-autocompletes.js"></script>
    </body>

    </html>
        <?php

    }//end echoUserTrips()


}//end class
