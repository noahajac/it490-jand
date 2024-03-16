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
        <style>
            main{
                margin: 0 auto;
                padding: 20px;
            }
            main h1{
                text-align: center;
            }
            .preference-container{
                display: flex;
                flex-direction: column;
                align-items: center;
                gap: 20px;
                padding: 10px;
            }
            .preference{
                padding: 15px;
            }
            .preference input{
                padding: 10px;
            }
            .destination{
                font-style: bold;
                font-size: 120%;
            }
        </style>
    </head>

    <body>
        <?php echo \JAND\Frontend\Includes\Elements\Nav::echoNav(); ?>
      <main>
        <h1>Set Your Travel Preferences</h1>
        <div class="preference-container">
        
            <form name="input-preference" id="input-preference" action="#" method="post">

                <h3>Destinations to Visit</h3>
        <div class="preference">
                <p class="destination">Outdoor Destinations</p>
                <input type="checkbox" id="mountains" name="mountains" value="mountains">
                <label for="mountains">Mountains</label>
                <input type="checkbox" id="park" name="park" value="park">
                <label for="park">National Parks</label>
                <input type="checkbox" id="waterfall" name="waterfall" value="waterfall">
                <label for="waterfall">Waterfalls</label><br>
        </div>
        <div class="preference">
                <p class="destination">Historical Destinations</p>
                <input type="checkbox" id="museum" name="museum" value="muesum">
                <label for="museum">Museums</label>
                <input type="checkbox" id="castle" name="castle" value="castle">
                <label for="castle">Castles</label><br>
        </div>
        <div class="preference">
                <p class="destination">Urban Destinations</p>
                <input type="checkbox" id="market" name="market" value="market">
                <label for="market">Markets</label>
                <input type="checkbox" id="boutique" name="boutique" value="boutique">
                <label for="boutique">Boutiques</label>
                <input type="checkbox" id="dining" name="dining" value="dining">
                <label for="dining">Dining Restaurants</label><br>
        </div>
        <div class="preference">
                <p class="destination">Adventure Destinations</p>
                <input type="checkbox" id="theme-park" name="theme-park" value="theme-park">
                <label for="theme-park">Theme Parks</label>
                <input type="checkbox" id="skiing" name="skiing" value="skiing">
                <label for="skiing">Skiing Locations</label>
                <input type="checkbox" id="hiking" name="hiking" value="hiking">
                <label for="Hiking">Hiking Trails</label><br>
        </div>
        <div class="preference">
                <p class="destination">Coastal Destinations</p>
                <input type="checkbox" id="beach" name="beach" value="beach">
                <label for="beach">Beach</label>
                <input type="checkbox" id="resort" name="resort" value="resort">
                <label for="resort">Resort</label><br>
        </div>
        <div class="preference">
                <p class="destination">Religious Destinations</p>
                <input type="checkbox" id="church" name="chruch" value="church">
                <label for="church">Church</label>
                <input type="checkbox" id="temple" name="temple" value="temple">
                <label for="temple">Temple</label>
                <input type="checkbox" id="mosque" name="mosque" value="mosque">
                <label for="mosque">Mosque</label><br>
        </div>
                <input type="submit" value="Save" name="submit">
            </form>
        </div>
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
    </body>

    </html>
        <?php

    }//end echoUserPreferences()


}//end class