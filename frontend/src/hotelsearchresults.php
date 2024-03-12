
<?php


//TESTING THIS CODE FOR PROCESSING THE API 

// when processing the POST request if the form has been submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Retrieve form data...
    $destId = $_POST['destination'];
    $adults = $_POST['adults'];
    $children = $_POST['children'] ?? '';
    $room = $_POST['room'] ?? 1;

    // Converts dates to the proper format
    $arrivalDate = date('Y-m-d', strtotime($_POST['arrival_date']));
    $departureDate = date('Y-m-d', strtotime($_POST['departure_date']));

    // Initializing  cURL session from Booking API
    $curl = curl_init();

    // Setting up the cURL options 
    curl_setopt_array($curl, [
        CURLOPT_URL => "https://booking-com15.p.rapidapi.com/api/v1/hotels/searchHotels?dest_id=" . urlencode($destId) . "&search_type=CITY&arrival_date=" . $arrivalDate . "&departure_date=" . $departureDate . "&adults=" . $adults . "&children_age=" . $children . "&room_qty=" . $room . "&page_number=1&languagecode=en-us&currency_code=AED",
        CURLOPT_RETURNTRANSFER => true,
        CURLOPT_ENCODING => "",
        CURLOPT_MAXREDIRS => 10,
        CURLOPT_TIMEOUT => 30,
        CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
        CURLOPT_CUSTOMREQUEST => "GET",
        CURLOPT_HTTPHEADER => [
            "X-RapidAPI-Host: booking-com15.p.rapidapi.com",
            "X-RapidAPI-Key: 414b941973msh4e2ab818fa89f04p147906jsn1c52c47ab507" // API Key
        ],
    ]);

    // this code execustes cURL session and gets the response
    $response = curl_exec($curl);
    $err = curl_error($curl);

    // this code closes cURL session
    curl_close($curl);

    // Checks for any errors in the cURL request
    if ($err) {
        $result = "cURL Error #:" . $err;
    } else {
        // Decode JSON response
        $data = json_decode($response, true);
        // Generate HTML to display results (to be implemented below)
        $result = generateResultsHtml($data);
    }
} else {
    $result = "No search data provided. Please enter search criteria.";
}

function generateResultsHtml($data) {
    if (isset($data['hotels']) && count($data['hotels']) > 0) {
        $html = "<h2>Search Results</h2><div class='hotel-results'>";
        foreach ($data['hotels'] as $hotel) {
            $html .= "<div class='hotel'>";
            $html .= "<h3>" . htmlspecialchars($hotel['hotel_name']) . "</h3>";
            $html .= "<p>Address: " . htmlspecialchars($hotel['address']) . "</p>";
            $html .= "<p>Rating: " . htmlspecialchars($hotel['star_rating']) . " stars</p>";
            $html .= "<p>Score: " . htmlspecialchars($hotel['review_score']) . "</p>";
            $html .= "</div>";
        }
        $html .= "</div>";
        return $html;
    } else {
        return "<p>No results found for the provided search criteria.</p>";
    }
}

//this should provide a new page with the results
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Hotel Search Results</title>
    <link rel="stylesheet" href="bookingPageStyle.css">
</head>
<body>
    <?php echo $result; ?>
</body>
</html>
