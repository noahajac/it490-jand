<?php
require_once '../../common/EmailHandler.php'; 

// this function helps process the booking data
function processBooking($bookingData) {
    if (empty($bookingData['customerEmail']) || !filter_var($bookingData['customerEmail'], FILTER_VALIDATE_EMAIL)) {
        return false;  // Return false if the email is invalid.
    }
        return true;
}

// Check if the form has been submitted
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $bookingData = $_POST; 

    // Process the booking
    if (processBooking($bookingData)) {
        // Prepare booking details for the email
        $bookingDetails = [
            'flight' => [
                'departureDateTime' => $bookingData['departureDateTime'],
                'departureAirport' => $bookingData['departureAirport'],
                'arrivalAirport' => $bookingData['arrivalAirport'],
                'airlineName' => $bookingData['airlineName'],
                'returnDateTime' => $bookingData['returnDateTime'],
                'returnAirport' => $bookingData['returnAirport']
            ],
            'hotel' => [
                'hotelName' => $bookingData['hotelName'],
                'checkInDate' => $bookingData['checkInDate'],
                'checkOutDate' => $bookingData['checkOutDate'],
                'guestCount' => $bookingData['guestCount']
            ]
        ];

        // Send the booking confirmation email
        sendBookingConfirmationEmail($bookingData['customerEmail'], $bookingData['customerName'], $bookingDetails);

        echo "Booking successful! Confirmation email sent.";
    } else {
        echo "Failed to process booking.";
    }
} else {
    echo "Invalid request method.";
}
