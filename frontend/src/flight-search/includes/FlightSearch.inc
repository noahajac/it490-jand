<?php
/**
 * Contains frontend flight search page.
 *
 * @package JAND\Frontend\FlightSearch\Includes\FlightSearch
 */

namespace JAND\Frontend\FlightSearch\Includes;

use JAND\Common\Trips\AirportCity;
use JAND\Frontend\Includes\LogSender;

/**
 * Flight search page.
 */
abstract class FlightSearch
{


    /**
     * Echoes flight search page.
     *
     * @param String[]                             $errors      Errors to show.
     * @param \JAND\Common\Trips\FlightItinerary[] $itineraries Itineraries to show.
     * @param AirportCity                          $originCity  Searched origin city.
     * @param AirportCity                          $destCity    Searched destination city.
     * @param \DateTime                            $startDate   Searched start date.
     * @param \DateTime                            $endDate     Searched end date.
     * @param integer                              $adults      Searched adults.
     * @param integer                              $children    Searched children.
     * @param boolean                              $oneWay      Whether search was one way.
     * @param boolean                              $alert       Whether price alert was requested.
     *
     * @return void
     */
    private static function echoFlightSearch(
        array $errors=[],
        array $itineraries=[],
        ?AirportCity $originCity=null,
        ?AirportCity $destCity=null,
        ?\DateTime $startDate=null,
        ?\DateTime $endDate=null,
        ?int $adults=null,
        ?int $children=null,
        ?bool $oneWay=null,
        ?bool $alert=false
    ) {
        try {
            $session = \JAND\Frontend\Includes\SessionManager::getSession();

            if (!$session) {
                http_response_code(401);
                exit();
            }

            ?>

        <!DOCTYPE html>
        <html lang="en">

        <head>
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <?php echo \JAND\Frontend\Includes\Elements\Head::echoHead(); ?>
        </head>

        <body>
            <?php echo \JAND\Frontend\Includes\Elements\Nav::echoNav(); ?>
        <main>
            <?php
            if (count($itineraries) > 0) {
                if (!$alert) {
                    ?>
                <form method="post">
                    <input type="hidden" name="trip" value=
                    <?php
                    if ($oneWay) {
                        echo '"one-way"';
                    } else {
                        echo '"round-trip"';
                    }
                    ?>
                    >
                    <input type="hidden" name="from" value="<?= $originCity->getCode(); ?>">
                    <input type="hidden" name="to" value="<?= $destCity->getCode(); ?>">
                    <input type="hidden" name="departure" value="<?= $startDate->format('Y-m-d'); ?>">
                    <input type="hidden" name="return" value="<?= $endDate->format('Y-m-d'); ?>">
                    <input type="hidden" name="adults" value="<?= $adults; ?>">
                    <input type="hidden" name="children" value="<?= $children; ?>">
                    <button type="submit" class="btn-submit" name="alert" value="true">Get Price Alerts</button>
                </form>
                    <?php
                } else {
                    ?>
                    <h2>You will be notified if the price drops for this search.</h2>
                    <?php
                }//end if

                foreach ($itineraries as &$itinerary) {
                    ?>
                    <div class="flight-result">
                    <table class="table-borders">
                        <tr>
                            <th>From <?= $itinerary->getOrigin()->getName(); ?></th>
                            <th>To <?= $itinerary->getDestination()->getName(); ?></th>
                        </tr>
                        <tr>
                            <th><?= $itinerary->getStartDate()->format('Y-m-d'); ?></th>
                            <th><?= $itinerary->getEndDate()->format('Y-m-d'); ?></th>
                        </tr>
                        <tr>
                            <th colspan="2">$<?= $itinerary->getGrandTotal(); ?></th>
                        </tr>
                        <tr>
                            <td><?= $itinerary->getAdults(); ?> Adults</td>
                            <td><?= $itinerary->getChildren(); ?> Children</td>
                        </tr>
                        <tr>
                            <td colspan="2">
                                <a href="/bookings/create?type=flight&key=<?= $itinerary->getItineraryId(); ?>"
                            >Book Now</a></td>
                        </tr>
                    </table>
                    <table class="table-borders">
                        <tr>
                            <th colspan="4">Outbound</th>
                        <?php
                        foreach ($itinerary->getOutboundSegments() as &$outSegment) {
                            ?>
                                <tr>
                                    <th colspan="3">
                                    <?= $outSegment->getAirline()->getName().' '.$outSegment->getFlightNo(); ?>
                                    </th>
                                    <td>
                                        <a href="/reviews?type=airline&key=<?= $outSegment->getAirline()->getCode(); ?>"
                                        >Reviews</a>
                                    </td>
                                </tr>
                                <tr>
                                <td><?= $outSegment->getDepartAirport()->getName(); ?></td>
                                <td><?= $outSegment->getArrivalAirport()->getName(); ?></td>
                                <td><?= $outSegment->getDepartTime()->format('Y-m-d g:i A'); ?></td>
                                <td><?= $outSegment->getArrivalTime()->format('Y-m-d g:i A'); ?></td>
                             </tr>
                                <?php
                        }
                        ?>
                        </tr>
                    </table>
                        <?php if (!$itinerary->getOneWay()) { ?>
                        <table class="table-borders">
                        <tr>
                            <th colspan="4">Return</th>
                            <?php
                            foreach ($itinerary->getReturnSegments() as &$returnSegment) {
                                ?>
                                <tr>
                                    <th colspan="3">
                                    <?= $returnSegment->getAirline()->getName().' '.$returnSegment->getFlightNo(); ?>
                                    </th>
                                    <td>
                                        <a
                                        href="/reviews?type=airline&key=<?= $returnSegment->getAirline()->getCode(); ?>"
                                        >Reviews</a>
                                    </td>
                                </tr>
                                <tr>
                                <td><?= $returnSegment->getDepartAirport()->getName(); ?></td>
                                <td><?= $returnSegment->getArrivalAirport()->getName(); ?></td>
                                <td><?= $returnSegment->getDepartTime()->format('Y-m-d g:i A'); ?></td>
                                <td><?= $returnSegment->getArrivalTime()->format('Y-m-d g:i A'); ?></td>
                             </tr>
                                <?php
                            }
                            ?>
                        </tr>
                    </table>
                            <?php
                        }//end if
                        ?>
                    </div>
                        <?php
                }//end foreach
            } else {
                ?>
            <div class="main-container">
        <div class="booking-form">

            <h2 class="title-form">Search for Flights</h2>

                <?php foreach ($errors as $error) { ?>
          <p class="error"><?php echo $error; ?></p>
                <?php } ?>

            <form method="post" id="search">
            <div class="input-group">
                    <label for="trip">Trip:</label>
                    <select id="trip" name="trip" class="form-control">
                        <option value="round-trip" selected>Round-Trip</option>
                        <option value="one-way">One-Way</option>
                    </select>
                </div>

                <div class="input-group">
                    <label for="from">From:</label>
                    <input type="text" id="from-display" placeholder= "Leaving From" required>
                    <input type="hidden" id="from" name="from">
                </div>

                <div class="input-group">
                    <label for="to">To:</label>
                    <input type="text"
                <?php
                $prefilledTo = filter_input(INPUT_GET, 'to', FILTER_SANITIZE_FULL_SPECIAL_CHARS);

                if (!empty($prefilledTo)) {
                    echo 'value="'.$prefilledTo.'"';
                }
                ?>
                    id="to-display" placeholder="Going To" required>
                    <input type="hidden" id="to" name="to">
                </div>

                <div class="input-group">
                    <label for="departure">Departure:</label>
                    <input type="date" id="departure" name="departure" placeholder="Leaving From" required>
                </div>

                <div class="input-group">
                    <label for="return">Return:</label>
                    <input type="date" id="return" name="return">
                </div>

                <div class="input-group">
                    <label>Travelers:</label>
                    <input type="number" id="adults" name="adults" placeholder="Adults" min="1" required>
                    <input type="number" id="children" name="children" placeholder="Children" min="0" required>
                </div>

                <input type="submit" id="search-submit" class= "btn-submit" value="Search">

            </form>
            </div>
        </div>
                <?php
            }//end if
            ?>
        </main>
            <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
        <script src="./scripts/city-autocomplete.js"></script>
            <?php
            if (!empty($prefilledTo)) {
                ?>
        <script>
            if (toInputField)
                toInputField.dispatchEvent(new Event('change'));
        </script>
                <?php
            }
            ?>
        </body>
        </html>

            <?php
        } catch (\Exception $e) {
            LogSender::sendLog('Error in echoFlightSearch: '.$e->getMessage());
            echo '<p>An error occurred while processing the flight search. Please try again later.</p>';
        }//end try

    }//end echoFlightSearch()


    /**
     * Runs the flight search page.
     *
     * @return void
     */
    public static function processFlightSearch()
    {
        try {
            LogSender::sendLog('Received a request for the flight search page.');

            if ($_SERVER['REQUEST_METHOD'] === 'POST') {
                $errorMsgs = [];

                $oneWay = filter_input(
                    INPUT_POST,
                    'trip',
                    FILTER_CALLBACK,
                    [
                        'options' => function ($input) {
                            if ($input === 'one-way') {
                                return true;
                            } else {
                                return false;
                            }
                        },
                    ]
                );

                $alert = filter_input(
                    INPUT_POST,
                    'alert',
                    FILTER_CALLBACK,
                    [
                        'options' => function ($input) {
                            if ($input === 'true') {
                                return true;
                            } else {
                                return false;
                            }
                        },
                    ]
                );

                if (!isset($alert)) {
                    $alert = false;
                }

                $origin      = filter_input(INPUT_POST, 'from', FILTER_SANITIZE_FULL_SPECIAL_CHARS);
                $destination = filter_input(INPUT_POST, 'to', FILTER_SANITIZE_FULL_SPECIAL_CHARS);
                $startDate   = filter_input(
                    INPUT_POST,
                    'departure',
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
                    'return',
                    FILTER_CALLBACK,
                    [
                        'options' => [
                            '\\JAND\\Frontend\\Includes\\DateCallback',
                            'checkDate',
                        ],
                    ]
                );
                $adults      = filter_input(INPUT_POST, 'adults', FILTER_SANITIZE_NUMBER_INT);
                $children    = filter_input(INPUT_POST, 'children', FILTER_SANITIZE_NUMBER_INT);

                if (empty($destination)) {
                      array_push($errorMsgs, 'You must input a destination.');
                }

                if (empty($origin)) {
                    array_push($errorMsgs, 'You must input a destination.');
                }

                if (empty($adults)) {
                    array_push($errorMsgs, 'You must enter number of adults.');
                }

                if (empty($children)) {
                    $children = 0;
                }

                $request  = new \JAND\Common\Messages\Shared\AirportCitySearchRequest(
                    $destination
                );
                $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);

                $destCity = $response->checkCode(strtoupper($destination));
                if (!$destCity) {
                      array_push($errorMsgs, 'Destination is not valid.');
                }

                $request  = new \JAND\Common\Messages\Shared\AirportCitySearchRequest(
                    $origin
                );
                $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);

                $originCity = $response->checkCode(strtoupper($origin));
                if (!$originCity) {
                      array_push($errorMsgs, 'Origin is not valid.');
                }

                if (empty($startDate)) {
                    array_push($errorMsgs, 'Start date must be valid.');
                }

                if (empty($endDate)) {
                    array_push($errorMsgs, 'End date must be valid.');
                }

                if (count($errorMsgs) > 0) {
                    static::echoFlightSearch($errorMsgs);
                    exit();
                }

                $session = \JAND\Frontend\Includes\SessionManager::getSession();
                if (!$session) {
                    http_response_code(401);
                    exit();
                }

                $request = new \JAND\Common\Messages\Shared\FlightItinerarySearchRequest(
                    $session->getSessionToken(),
                    $originCity,
                    $destCity,
                    $startDate,
                    $endDate,
                    $adults,
                    $children,
                    0,
                    $oneWay,
                    $alert
                );

                /**
                 * Flight itinerary search response.
                 *
                 * @var \JAND\Common\Messages\Shared\FlightItinerarySearchResponse $response Search response.
                 */
                $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);

                static::echoFlightSearch(
                    [],
                    $response->getFlightItineraries(),
                    $originCity,
                    $destCity,
                    $startDate,
                    $endDate,
                    $adults,
                    $children,
                    $oneWay,
                    $alert
                );
            } else {
                static::echoFlightSearch();
            }//end if
        } catch (\Exception $e) {
            LogSender::sendLog('Error in processFlightSearch: '.$e->getMessage());
            $errorMsgs = ['An error occurred while processing the flight search. Please try again later.'];
            static::echoFlightSearch($errorMsgs);
        }//end try

    }//end processFlightSearch()


}//end class
