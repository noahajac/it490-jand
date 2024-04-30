<?php
// Sends an email to the customer with their booking details.
function sendBookingConfirmationEmail($email, $customerName, $bookingDetails) {
    $subject = 'Your Booking Confirmation';
    $senderName = 'JAND Travel';
    $year = date("Y");

    //the email content
    $message = "<!DOCTYPE html>
<html>
<head>
    <title>Your Booking Details</title>
    <style>
        body { font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif; background-color: #eeeeee; margin: 0; padding: 0; }
        .container { background-color: #ffffff; width: 100%; max-width: 650px; margin: auto; padding: 20px; }
        .header { background-color: #5cd1e6; color: white; padding: 10px 20px; text-align: center; }
        .content { padding: 20px; line-height: 1.6; }
        .footer { background-color: #f2f2f2; text-align: center; padding: 10px 20px; font-size: 12px; color: #666; }
        table { width: 100%; margin-top: 20px; border-collapse: collapse; }
        th, td {padding: 8px; text-align: left; border-bottom: 1px solid #dddddd; }
    </style>
</head>
<body>
    <div class='container'>
        <div class='header'>
            <h1>Booking Confirmation</h1>
        </div>
        <div class='content'>
            <p>Dear {$customerName},</p>
            <p>Thank you for booking with Jand Travel. Here are the details of your upcoming trip:</p>
            <table>
                <tr>
                    <th>Service</th>
                    <th>Details</th>
                </tr>";
    // this booking email will provide information on booking the flight and hotel
    //this will check whicH one was booked to be added in the email 
    // Add flight details if they exist
    if (isset($bookingDetails['flight'])) {
        $flight = $bookingDetails['flight'];
        $message .= "<tr>
                    <td>Flight</td>
                    <td>
                        From: {$flight['departureAirport']} to {$flight['arrivalAirport']}<br>
                        Departure: {$flight['departureDateTime']}<br>
                        Airline: {$flight['airlineName']}<br>
                        Return: {$flight['returnDateTime']} from {$flight['returnAirport']}
                    </td>
                </tr>";
    }

    // Add hotel details if they exist
    if (isset($bookingDetails['hotel'])) {
        $hotel = $bookingDetails['hotel'];
        $message .= "<tr>
                    <td>Hotel</td>
                    <td>
                        Hotel Name: {$hotel['hotelName']}<br>
                        Check-in: {$hotel['checkInDate']}<br>
                        Check-out: {$hotel['checkOutDate']}<br>
                        Number of Guests: {$hotel['guestCount']}
                    </td>
                </tr>";
    }

    $message .= "</table>
            <p>If you have any questions, feel free to contact our customer support team. Happy Travels!</p>
        </div>
        <div class='footer'>
            © {$year} {$senderName}. All rights reserved.
        </div>
    </div>
</body>
</html>";

    $headers = "MIME-Version: 1.0\r\n";
    $headers .= "Content-type: text/html; charset=UTF-8\r\n";
    $headers .= "From: no-reply@jand-travel.com\r\n";

    mail($email, $subject, $message, $headers);
}
