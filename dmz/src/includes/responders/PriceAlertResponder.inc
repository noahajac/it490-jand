<?php
/**
 * Contains the responder for price alerts emails.
 *
 * @package JAND\Dmz\Includes\Responders\PriceAlertResponder
 */

namespace JAND\Dmz\Includes\Responders;

use JAND\Common\Messages\DbConnector\PriceAlertRequest;
use JAND\Common\Messages\DbConnector\PriceAlertResponse;
use JAND\Common\Trips\FlightItinerary;

/**
 * Responds to price alert requests.
 */
abstract class PriceAlertResponder
{


    /**
     * Responds to a create booking request.
     *
     * @param PriceAlertRequest $request Create request.
     *
     * @return PriceAlertResponse Response to request.
     */
    public static function respondToRequest(PriceAlertRequest $request)
    {
        $booking = $request->getItinerary();

        $message = "
        <html>
        <head>
            <title>JAND Price Alert</title>
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
                    <h1>Price Alert</h1>
                </div>
                <div class='content'>
                    <p>You have requested to receive an alert when prices drop for the following flight:</p>
                    <table>
                        <tr>
                            <th>Service</th>
                            <th>Details</th>
                        </tr>";

            $message .= '<tr>
                            <td>Flight</td>
                            <td>
                                From: '.$booking->getOrigin()->getCode();

            $message .= ' to '.$booking->getDestination()->getCode().'<br>
                                Departure: '.$booking->getStartDate()->format('Y-m-d').'<br>
                                Return: '.$booking->getEndDate()->format('Y-m-d').'
                            </td>
                        </tr>';

            $message .= "</table>
                    <p>Visit JAND Travel's flight search to see the new prices.</p>
                </div>
            </div>
        </body>
        </html>";

        $to        = $request->getEmail();
        $subject   = 'JAND Flight Price Alert';
        $headers[] = 'From: jand@srv01gr.local.noahjacobson.com';
        $headers[] = 'MIME-Version: 1.0';
        $headers[] = 'Content-Type: text/html; charset=UTF-8';

        mail($to, $subject, $message, implode("\r\n", $headers));

        return new PriceAlertResponse();

    }//end respondToRequest()


}//end class
