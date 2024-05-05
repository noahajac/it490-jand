<?php
/**
 * Contains frontend user trips creation/update page.
 *
 * @package JAND\Frontend\UserTrips\Create\Includes\CreateUserTrip
 */

namespace JAND\Frontend\UserTrips\Create\Includes;

use JAND\Frontend\Includes\LogSender;

/**
 * User trips creation/update page.
 */
abstract class CreateUserTrip
{


    /**
     * Echoes user trips create/update page.
     *
     * @param string[] $errors             Errors to show.
     * @param string   $destination        Prefill destination field.
     * @param string   $destinationDisplay Prefill destination display field.
     * @param string   $startDate          Prefill start date field.
     * @param string   $endDate            Prefill end date field.
     * @param boolean  $showDelete         Show delete button.
     *
     * @return void
     */
    private static function echoCreateUserTrip(
        array $errors=[],
        ?string $destination=null,
        ?string $destinationDisplay=null,
        ?string $startDate=null,
        ?string $endDate=null,
        bool $showDelete=false
    ) {
        ?>

    <!DOCTYPE html>
    <html lang="en">

    <head>
        <?php echo \JAND\Frontend\Includes\Elements\Head::echoHead(); ?>
    </head>

    <body>
        <?php echo \JAND\Frontend\Includes\Elements\Nav::echoNav(); ?>
      <main>
        <div class="create-trips-ctr">
        <?php foreach ($errors as $error) { ?>
          <p class="error"><?php echo $error; ?></p>
        <?php } ?>
        <form method="post" id="create-trip-form">
        <h3 class="trip-heading">Trip Details</h3>
            <table>
                <tr>
                    <th><label for="destination-display">Destination:</label></th>
                    <td><input type="text" id="destination-display" value="<?= $destinationDisplay; ?>" required></td>
                </tr>
                <tr>
                    <th><label for="start-date">Start Date:</label></th>
                    <td><input type="date" id="start-date" value="<?= $startDate; ?>" name="start-date" required></td>
                </tr>
                <tr>
                    <th><label for="end-date">End Date:</label></th>
                    <td><input type="date" id="end-date" value="<?= $endDate; ?>" name="end-date" required></td>
                </tr>

                <input type="hidden" name="destination" id="destination" value="<?= $destination; ?>">

                <tr>
                    <td colspan="2"><input type="submit" id="create-submit" 
                    <?php
                    if ($showDelete) {
                        echo 'value="Update"';
                    } else {
                        echo 'value="Create"';
                    }
                    ?>
                    ></td>
                </tr>
            </table>
        </form>
        <?php if ($showDelete) { ?>
        <br>
        <form method="post" id="delete-trip-btn">
            <button id="delete" name="delete" value="on" type="submit">Delete this Trip</button>
        </form>
        <?php } ?>
        </div>
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
        <script src="./scripts/destination-autocomplete.js"></script>
    </body>

    </html>
        <?php

    }//end echoCreateUserTrip()


    /**
     * Starts create/update user trip page.
     *
     * @return void
     */
    public static function bootstrapCreateUserTrip()
    {
        $session = \JAND\Frontend\Includes\SessionManager::getSession();

        LogSender::sendLog('Received a request for the user trips create/update page.');

        if (!$session) {
            http_response_code(401);
            exit();
        }

        $tripToUpdate = filter_input(INPUT_GET, 'id', FILTER_VALIDATE_INT);

        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            $delete    = filter_input(INPUT_POST, 'delete', FILTER_VALIDATE_BOOL);
            $errorMsgs = [];

            if ($tripToUpdate && $delete) {
                // User requested to delete trip.
                $request = new \JAND\Common\Messages\Frontend\DeleteUserTripRequest(
                    \JAND\Frontend\Includes\SessionManager::getSession()->getSessionToken(),
                    $tripToUpdate
                );
                \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);
                header('Location: ..');
                exit();
            } else {
                $destination = filter_input(INPUT_POST, 'destination', FILTER_SANITIZE_FULL_SPECIAL_CHARS);
                $startDate   = filter_input(
                    INPUT_POST,
                    'start-date',
                    FILTER_CALLBACK,
                    [
                        'options' => [
                            '\\JAND\\Frontend\\Includes\\DateCallback',
                            'checkDate',
                        ],
                    ]
                );
                $endDate     = filter_input(
                    INPUT_POST,
                    'end-date',
                    FILTER_CALLBACK,
                    [
                        'options' => [
                            '\\JAND\\Frontend\\Includes\\DateCallback',
                            'checkDate',
                        ],
                    ]
                );

                if (empty($destination)) {
                    array_push($errorMsgs, 'You must input a destination.');
                }

                $request  = new \JAND\Common\Messages\Shared\AirportCitySearchRequest(
                    $destination
                );
                $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);

                $city = $response->checkCode(strtoupper($destination));
                if (!$city) {
                    array_push($errorMsgs, 'Destination is not valid.');
                }

                if (empty($startDate)) {
                    array_push($errorMsgs, 'Start date must be valid.');
                }

                if (empty($endDate)) {
                    array_push($errorMsgs, 'End date must be valid.');
                }

                if (count($errorMsgs) > 0) {
                    static::echoCreateUserTrip($errorMsgs);
                    exit();
                }

                $request = new \JAND\Common\Messages\Frontend\CreateUserTripRequest(
                    \JAND\Frontend\Includes\SessionManager::getSession()->getSessionToken(),
                    new \JAND\Common\Trips\UserTrip(
                        $tripToUpdate,
                        $city,
                        $startDate,
                        $endDate
                    )
                );
                \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);

                header('Location: ..');
                exit();
            }//end if
        } else {
            if (!empty($tripToUpdate)) {
                // User is editing an existing trip.
                $request  = new \JAND\Common\Messages\Frontend\GetUserTripsRequest(
                    \JAND\Frontend\Includes\SessionManager::getSession()->getSessionToken()
                );
                $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);

                $destination        = null;
                $destinationDisplay = null;
                $startDate          = null;
                $endDate            = null;
                $showDelete         = false;

                foreach ($response->getUserTrips() as &$trip) {
                    if ($trip->getTripId() === $tripToUpdate) {
                        $showDelete         = true;
                        $destinationObj     = $trip->getTripDestination();
                        $destination        = $destinationObj->getCode();
                        $destinationDisplay = $destinationObj->getName();
                        $startDate          = $trip->getTripStart()->format('Y-m-d');
                        $endDate            = $trip->getTripEnd()->format('Y-m-d');

                        break;
                    }
                }

                static::echoCreateUserTrip([], $destination, $destinationDisplay, $startDate, $endDate, $showDelete);
                exit();
            } else {
                static::echoCreateUserTrip();
                exit();
            }//end if
        }//end if

    }//end bootstrapCreateUserTrip()


}//end class
