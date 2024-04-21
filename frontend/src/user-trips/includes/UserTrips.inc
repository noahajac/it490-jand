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
        $session = \JAND\Frontend\Includes\SessionManager::getSession();

        if (!$session) {
            http_response_code(401);
            exit();
        }

        $request  = new \JAND\Common\Messages\Frontend\GetUserTripsRequest(
            \JAND\Frontend\Includes\SessionManager::getSession()->getSessionToken()
        );
        $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);
        ?>

    <!DOCTYPE html>
    <html lang="en">

    <head>
        <?php echo \JAND\Frontend\Includes\Elements\Head::echoHead(); ?>
    </head>

    <body>
        <?php echo \JAND\Frontend\Includes\Elements\Nav::echoNav(); ?>
      <main>
        <div class="trips-container">
        <h3 class="create-heading">Create Your Trips</h3>
        <a id="create-new-trip" href="./create">Create new trip</a>
        <?php
        $trips = $response->getUserTrips();

        if (count($trips) < 1) {
            ?>
            <h2>You have no trips.</h2> 
            <?php
        } else {
            ?>
            <table class="table-borders">
                <tr>
                    <th>Destination</th>
                    <th>Start Date</th>
                    <th>End Date</th>
                </tr>
                <?php foreach ($trips as &$trip) { ?>
                    <tr>
                        <td><?= $trip->getTripDestination()->getName(); ?></td>
                        <td><?= $trip->getTripStart()->format('M j, Y'); ?></td>
                        <td><?= $trip->getTripEnd()->format('M j, Y'); ?></td>
                        <td><a href="./create/?id=<?= $trip->getTripId(); ?>">Edit</a></td>
                    </tr>
                <?php } ?>
            </table>
                <?php
        }//end if
        ?>
        </div>
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
    </body>

    </html>
        <?php

    }//end echoUserTrips()


}//end class
