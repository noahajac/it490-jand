<?php
/**
 * Contains frontend hotel search page.
 *
 * @package JAND\Frontend\HotelSearch\Includes\HotelSearch
 */

namespace JAND\Frontend\HotelSearch\Includes;

/**
 * Hotel search page.
 */
abstract class HotelSearch
{


    /**
     * Echoes hotel search page.
     *
     * @param String[]                            $errors      Errors to show.
     * @param \JAND\Common\Trips\HotelItinerary[] $itineraries Itineraries to show.
     *
     * @return void
     */
    private static function echoHotelSearch(array $errors=[], array $itineraries=[])
    {
        $session = \JAND\Frontend\Includes\SessionManager::getSession();

        if (!$session) {
            http_response_code(401);
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
            <?php
            if (count($itineraries) > 0) {
                foreach ($itineraries as &$itinerary) {
                    ?>
                    <div class="flight-result">
                    <table class="table-borders">
                        <tr>
                            <th colspan="2"><?= $itinerary->getHotel()->getName(); ?></th>
                        </tr>
                        <tr>
                            <th><?= $itinerary->getStartDate()->format('Y-m-d'); ?></th>
                            <th><?= $itinerary->getEndDate()->format('Y-m-d'); ?></th>
                        </tr>
                        <tr>
                            <th colspan="2">$<?= $itinerary->getGrandTotal(); ?></th>
                        </tr>
                        <tr>
                        <td>
                             <a href="/bookings/create?type=hotel&key=<?= $itinerary->getHotel()->getHotelId(); ?>"
                                        >Book Now</a>
                                    </td>
                        <td>
                             <a href="/reviews?type=hotel&key=<?= $itinerary->getHotel()->getHotelId(); ?>"
                                        >Reviews</a>
                                    </td>
                        </tr>
                    </table>
                    </div>
                    <?php
                }//end foreach
            } else {
                ?>
            <div class="main-container">
        <div class="booking-form">
            
            <h2 class="title-form">Search for Hotels</h2>
            
                <?php foreach ($errors as $error) { ?>
          <p class="error"><?php echo $error; ?></p>
                <?php } ?>

            <form method="post">
                <div class="input-group">
                    <label for="destination">Destination:</label>
                    <input type="text" id="destination-display" placeholder="Going To?" required> 
                    <input type="hidden" id="destination" name="destination"> 
                </div>

                <div class="input-group date-group">
                    <div class="date-labels">
                        <label for="check-in">Check-in:</label> 
                        <input type="date" id="check-in" name="check-in" required>
                        <label for="check-out" class="departure-label">Check-out:</label> 
                        <input type="date" id="check-out" name="check-out" required>
                    </div>
                </div>

                <div class="input-group">
                    <label>Travelers:</label>
                    <input type="number" id="adults" name="adults" placeholder="Adults" min="1" max="10" required>
                </div>
            
                <input type="submit" id="search-submit" class="btn-submit" value="Search">
            
            </form>
            </div>
        </div>
                <?php
            }//end if
            ?>
        </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
        <script src="./scripts/city-autocomplete.js"></script>
        </body>
        </html>

        <?php

    }//end echoHotelSearch()


    /**
     * Runs the hotel search page.
     *
     * @return void
     */
    public static function processHotelSearch()
    {
        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            $errorMsgs = [];

            $destination = filter_input(INPUT_POST, 'destination', FILTER_SANITIZE_FULL_SPECIAL_CHARS);
            $checkIn     = filter_input(
                INPUT_POST,
                'check-in',
                FILTER_CALLBACK,
                [
                    'options' => [
                        '\\JAND\\Frontend\\Includes\\DateCallback',
                        'checkDate',
                    ],
                ]
            );
            $checkOut    = filter_input(
                INPUT_POST,
                'check-out',
                FILTER_CALLBACK,
                [
                    'options' => [
                        '\\JAND\\Frontend\\Includes\\DateCallback',
                        'checkDate',
                    ],
                ]
            );
            $adults      = filter_input(INPUT_POST, 'adults', FILTER_SANITIZE_NUMBER_INT);

            if (empty($destination)) {
                array_push($errorMsgs, 'You must input a destination.');
            }

            if (empty($adults)) {
                array_push($errorMsgs, 'You must enter number of adults.');
            }

            $request  = new \JAND\Common\Messages\Shared\AirportCitySearchRequest(
                $destination
            );
            $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);

            $destinationCity = $response->checkCode(strtoupper($destination));
            if (!$destinationCity) {
                array_push($errorMsgs, 'Destination is not valid.');
            }

            if (empty($checkIn)) {
                array_push($errorMsgs, 'Check in must be valid.');
            }

            if (empty($checkOut)) {
                array_push($errorMsgs, 'Check out must be valid.');
            }

            if (count($errorMsgs) > 0) {
                static::echoHotelSearch($errorMsgs);
                exit();
            }

            $request = new \JAND\Common\Messages\Shared\HotelItinerarySearchRequest(
                $destinationCity,
                $checkIn,
                $checkOut,
                $adults
            );

            /**
             * Hotel itinerary search response.
             *
             * @var \JAND\Common\Messages\Shared\HotelItinerarySearchResponse $response Search response.
             */
            $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);

            static::echoHotelSearch([], $response->getHotelItineraries());
        } else {
            static::echoHotelSearch();
        }//end if

    }//end processHotelSearch()


}//end class
