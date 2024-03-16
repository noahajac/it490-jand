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
        <style>
            main{
                margin: 0 auto;
                padding: 20px;
            }
            main h1{
                text-align: center;
            }
            .rec-container{
                display: flex;
                flex-direction: column;
                gap: 20px;
                align-items: center;
            }
            .rec{
                padding: 25px;
            }
            .rec table->tr th,td{
                border: 1px solid black;
                padding: 10px;
            }
            .rec-heading{
                padding-bottom: 5px;
            }
        </style>

    </head>

    <body>
        <?php echo \JAND\Frontend\Includes\Elements\Nav::echoNav(); ?>
      <main>
        <!-- -->
        <h1>Recommendations for You</h1>
        <div class="rec-container">
        <div class="rec">
            <h3 class="rec-heading">Flights</h3>
            <table>
                <tr>
                    <th>Airlines</th>
                    <th>Origin</th>
                    <th>Destination</th>
                    <th>Date</th>
                    <th>Price</th>
                </tr>
                <tr>
                    <td>United Airlines</td>
                    <td>Newark, NJ (EWR)</td>
                    <td>Mexico City, Mexico (MEX)</td>
                    <td>March 25, 2024</td>
                    <td>$550</td>
                </tr>
                <tr>
                    <td>Delta Airlines</td>
                    <td>Newark, NJ (EWR)</td>
                    <td>Mexico City, Mexico (MEX)</td>
                    <td>March 25, 2024</td>
                    <td>$500</td>
                </tr>
            </table>
        </div> 
        <div class="rec">
            <h3 class="rec-heading">Hotels</h3>
            <table>
                <tr>
                    <th>Hotels</th>
                    <th>Location</th>
                    <th>Room</th>
                    <th>Date</th>
                    <th>Price</th>
                </tr>
                <tr>
                    <td>Hotel 1</td>
                    <td>Mexico City, MX</td>
                    <td>2 Guests, 1 King Size Bed</td>
                    <td>March 25, 2024</td>
                    <td>$80 per night</td>
                </tr>
                <tr>
                    <td>Hotel 2</td>
                    <td>Mexico City, MX</td>
                    <td>2 Guests, 1 King Size Bed</td>
                    <td>March 25, 2024</td>
                    <td>$95 per night</td>
                </tr>
            </table>
        </div>
        <div class="rec">
            <h3 class="rec-heading">Attractions</h3>
            <table>
                <tr>
                    <th>Attractions</th>
                    <th>Location</th>
                    <th>Date</th>
                    <th>Price</th>
                    <th>Rating</th>
                </tr>
                <tr>
                    <td>Attraction 1</td>
                    <td>Mexico City, MX</td>
                    <td>March 25, 2024</td>
                    <td>$80 per person</td>
                    <td>4.5</td>
                </tr>
                <tr>
                    <td>Attraction 2</td>
                    <td>Mexico City, MX</td>
                    <td>March 25, 2024</td>
                    <td>Free</td>
                    <td>5</td>
                </tr>
            </table>
        </div> 
        </div>    
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
    </body>

    </html>
        <?php

    }//end echoRecommendations()


}//end class