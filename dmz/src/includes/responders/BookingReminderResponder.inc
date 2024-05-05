<?php
/**
 * Contains the responder for a booking reminder request.
 *
 * @package JAND\Dmz\Includes\Responders\BookingReminderResponder
 */

namespace JAND\Dmz\Includes\Responders;

use JAND\Common\Messages\DbConnector\BookingReminderRequest;
use JAND\Common\Messages\DbConnector\BookingReminderResponse;
use JAND\Common\Trips\FlightItinerary;

/**
 * Responds to booking reminder requests.
 */
abstract class BookingReminderResponder
{


    /**
     * Responds to a create booking request.
     *
     * @param BookingReminderRequest $request Create request.
     *
     * @return BookingReminderResponse Response to request.
     */
    public static function respondToRequest(BookingReminderRequest $request)
    {
        $booking = $request->getItinerary();

        $message = "
        <html>
        <head>
            <title>Your Booking Reminder</title>
            <style>
                body { font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif; background-color: #eeeeee; 
                    margin: 0; padding: 0; }
                .container { background-color: #ffffff; width: 100%; max-width: 650px; margin: auto; padding: 20px; }
                .header { background-color: #5cd1e6; color: white; padding: 10px 20px; text-align: center; }
                .content { padding: 20px; line-height: 1.6; }
                .footer { background-color: #f2f2f2; text-align: center; padding: 10px 20px; 
                    font-size: 12px; color: #666; }
                table { width: 100%; margin-top: 20px; border-collapse: collapse; }
                th, td {padding: 8px; text-align: left; border-bottom: 1px solid #dddddd; }
            </style>
        </head>
        <body>
            <div class='container'>
                <div class='header'>
                    <h1>Booking Reminder</h1>
                </div>
                <div class='content'>
                    <p>This is a friendly reminder from JAND travel regarding your upcoming booking:</p>
                    <table>
                        <tr>
                            <th>Service</th>
                            <th>Details</th>
                        </tr>";
            // This booking email will provide information on booking the flight and hotel.
            // This will check which one was booked to be added in the email.
            // Check if this booking is for a flight.
        if ($booking instanceof FlightItinerary) {
            $message .= '<tr>
                            <td>Flight</td>
                            <td>
                                From: '.$booking->getOrigin()->getName();

            $message .= ' to '.$booking->getDestination()->getName().'<br>
                                Departure: '.$booking->getStartDate()->format('Y-m-d').'<br>
                                Return: '.$booking->getEndDate()->format('Y-m-d').'
                            </td>
                        </tr>';
        } else {
            $message .= '<tr>
                            <td>Hotel</td>
                            <td>
                                Hotel Name: '.$booking->getHotel()->getName().'<br>
                                Check-in: '.$booking->getStartDate()->format('Y-m-d').'<br>
                                Check-out: '.$booking->getEndDate()->format('Y-m-d').'<br>
                                Number of Guests: '.$booking->getAdults().'
                            </td>
                        </tr>';
        }//end if

            $message .= '</table>
                    <p>If you have any questions, feel free to contact our customer support team. Happy Travels!</p>
                </div>
            </div>
        </body>
        </html>';

        $to        = $request->getEmail();
        $subject   = 'JAND Booking Reminder';
        $headers[] = 'From: jand@srv01gr.local.noahjacobson.com';
        $headers[] = 'MIME-Version: 1.0';
        $headers[] = 'Content-Type: text/html; charset=UTF-8';

        mail($to, $subject, $message, implode("\r\n", $headers));

        return new BookingReminderResponse();

    }//end respondToRequest()


}//end class
