<?php
/**
 * Contains frontend booking creation page.
 *
 * @package JAND\Frontend\Bookings\Create\Includes\CreateBooking
 */

namespace JAND\Frontend\Bookings\Create\Includes;

/**
 * Booking creation page.
 */
abstract class CreateBooking
{


    /**
     * Echoes booking create page.
     *
     * @return void
     */
    private static function echoCreateBooking()
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
        <form method="post" class="createpg">
            <table>
                <tr>
                    <th><label for="cc-num">Credit Card:</label></th>
                    <td><input type="text" title="Numbers only." pattern="\d+" minlength="8" maxlength="19" 
                    id="cc-num" required></td>
                </tr>
                <tr>
                    <th><label for="cc-expiration">Credit Card Expiration:</label></th>
                    <td><input min="<?= (new \DateTime('now'))->format('Y-m'); ?>" 
                    type="month" id="cc-expiration" required></td>
                </tr>
                <tr>
                    <th><label for="cc-cvv">CVV:</label></th>
                    <td><input type="text" title="Numbers only." 
                    pattern="\d+" minlength="3" maxlength="4" id="cc-cvv" required></td>
                </tr>

                <input type="hidden" name="destination" id="destination" >

                <tr>
                    <td colspan="2"><input type="submit" class="btn-submit" id="create-submit" value="Book"></td>
                </tr>
            </table>
        </form>
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
    </body>

    </html>
        <?php

    }//end echoCreateBooking()


    /**
     * Starts create booking page.
     *
     * @return void
     */
    public static function bootstrapCreateUserTrip()
    {
        $session = \JAND\Frontend\Includes\SessionManager::getSession();

        if (!$session) {
            http_response_code(401);
            exit();
        }

        $type = filter_input(INPUT_GET, 'type');
        $key  = filter_input(INPUT_GET, 'key', FILTER_VALIDATE_INT);

        if ($type === 'flight') {
            $type = 'flight';
        } else {
            $type = 'hotel';
        }

        if (empty($key)) {
            header('Location: ..');
            exit();
        }

        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            if ($type === 'flight') {
                $request = new \JAND\Common\Messages\Frontend\CreateBookingRequest(
                    \JAND\Frontend\Includes\SessionManager::getSession()->getSessionToken(),
                    new \JAND\Common\Trips\FlightItinerary(
                        $key,
                        [],
                        [],
                        null,
                        null,
                        null,
                        null,
                        0,
                        0
                    )
                );
            } else {
                $request = new \JAND\Common\Messages\Frontend\CreateBookingRequest(
                    \JAND\Frontend\Includes\SessionManager::getSession()->getSessionToken(),
                    new \JAND\Common\Trips\HotelItinerary(
                        $key,
                        null,
                        null,
                        null,
                        0,
                        0
                    )
                );
            }//end if

                \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);

                header('Location: ..');
                exit();
        } else {
                static::echoCreateBooking();
        }//end if

    }//end bootstrapCreateUserTrip()


}//end class
