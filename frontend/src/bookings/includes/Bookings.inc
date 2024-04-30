<?php
/**
 * Contains frontend bookings page.
 *
 * @package JAND\Frontend\Bookings\Includes\Bookings
 */

namespace JAND\Frontend\Bookings\Includes;

use JAND\Common\Messages\Frontend\GetBookingsResponse;

/**
 * User trips page.
 */
abstract class Bookings
{


    /**
     * Echoes user bookings page.
     *
     * @return void
     */
    public static function echoBookings()
    {
        $session = \JAND\Frontend\Includes\SessionManager::getSession();

        if (!$session) {
            http_response_code(401);
            exit();
        }

        $request = new \JAND\Common\Messages\Frontend\GetBookingsRequest(
            \JAND\Frontend\Includes\SessionManager::getSession()->getSessionToken()
        );
        /**
         * Response from DB.
         *
         * @var GetBookingsResponse $response Bookings.
         */
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
        <?php
        $flights = $response->getFlights();
        $hotels  = $response->getHotels();

        if (count($flights) < 1) {
            ?>
            <h2>You have no flights booked.</h2> 
            <?php
        } else {
            ?>
            <h2>Flights:</h2>
                <?php
                foreach ($flights as &$itinerary) {
                    ?>
                    <div class="flight-result">
                    <table class="table-borders">
                        <tr>
                            <th>From: <?= $itinerary->getOrigin()->getName(); ?></th>
                            <th>To: <?= $itinerary->getDestination()->getName(); ?></th>
                        </tr>
                        <tr>
                            <th>Departure:  <?= $itinerary->getStartDate()->format('Y-m-d'); ?></th>
                            <th>Return:  <?= $itinerary->getEndDate()->format('Y-m-d'); ?></th>
                        </tr>
                        <tr>
                            <th colspan="2">Price: $<?= $itinerary->getGrandTotal(); ?></th>
                        </tr>
                        <tr>
                            <td>Passenger: <?= $itinerary->getAdults(); ?> Adults</td>
                            <td>Passenger: <?= $itinerary->getChildren(); ?> Children</td>
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
                                <td><?= $outSegment->getDepartTime()->format('Y-m-d g:i A'); ?>Departure: </td>
                                <td><?= $outSegment->getArrivalTime()->format('Y-m-d g:i A'); ?>Arrival: </td>
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
                                <td><?= $returnSegment->getDepartTime()->format('Y-m-d g:i A'); ?>Departure: </td>
                                <td><?= $returnSegment->getArrivalTime()->format('Y-m-d g:i A'); ?>Arrival: </td>
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
                ?>
                <?php
        }//end if

        if (count($hotels) < 1) {
            ?>
            <h2>You have no hotels booked</h2> 
            <?php
        } else {
            ?>
            <h2>Hotels:</h2>
                <?php
                foreach ($hotels as &$itinerary) {
                    ?>
                    <div class="flight-result">
                    <table class="table-borders">
                        <tr>
                            <th colspan="2">Hotel: <?= $itinerary->getHotel()->getName(); ?></th>
                        </tr>
                        <tr>
                            <th>Check in: <?= $itinerary->getStartDate()->format('Y-m-d'); ?></th>
                            <th>CHeck Out: <?= $itinerary->getEndDate()->format('Y-m-d'); ?></th>
                        </tr>
                        <tr>
                            <th colspan="2">Price: $<?= $itinerary->getGrandTotal(); ?></th>
                        </tr>
                        <tr>
                        <td colspan="2">
                             <a href="/reviews?type=hotel&key=<?= $itinerary->getHotel()->getHotelId(); ?>"
                                        >Reviews</a>
                                    </td>
                        </tr>
                    </table>
                    </div>
                    <?php
                }//end foreach
                ?>
                <?php
        }//end if
        ?>

      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
    </body>

    </html>
        <?php

    }//end echoBookings()


}//end class
