<?php
/**
 * Contains the responder for a get airline reviews request.
 *
 * @package JAND\DbConnector\Includes\Responders\GetAirlineReviewsResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use JAND\Common\Trips\Airline;
use JAND\Common\Trips\AirlineReview;

/**
 * Responds to get airline review requests.
 */
abstract class GetAirlineReviewsResponder
{


    /**
     * Responds to a get airline reviews request.
     *
     * @param \JAND\Common\Messages\Frontend\GetAirlineReviewsRequest $request Get request.
     * @param \PDO                                                    $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\GetReviewsResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Frontend\GetAirlineReviewsRequest $request, \PDO $pdo)
    {
        $sessionToken = $request->getSessionToken();
        $airline      = $request->getAirline();

        $stmt = $pdo->prepare(
            'SELECT * FROM airline_reviews r, airlines a WHERE r.iata_code=:iataCode AND 
r.iata_code=a.iata_code'
        );
        $stmt->execute(
            [
                'iataCode' => $airline->getCode(),
            ]
        );
        $dbResults = $stmt->fetchAll();
        $stmt->closeCursor();

        $reviews = [];

        foreach ($dbResults as &$result) {
            array_push(
                $reviews,
                new AirlineReview(
                    $result['review_id'],
                    $result['rating'],
                    $result['comment'],
                    new Airline($result['iata_code'], $result['name'])
                )
            );
        }

        $stmt = $pdo->prepare(
            'SELECT r.*, a.* FROM airline_reviews r, airlines a, sessions s WHERE r.iata_code=:iataCode AND 
r.user_id=s.user_id AND s.session_token=:sessionToken AND a.iata_code=r.iata_code'
        );
        $stmt->execute(
            [
                'iataCode'     => $airline->getCode(),
                'sessionToken' => $sessionToken,
            ]
        );
        $own = $stmt->fetch();
        if ($own === false) {
            $own = null;
        } else {
            $own = new AirlineReview(
                $own['review_id'],
                $own['rating'],
                $own['comment'],
                new Airline($own['iata_code'], $own['name'])
            );
        }

        return new \JAND\Common\Messages\Frontend\GetReviewsResponse($reviews, $own);

    }//end respondToRequest()


}//end class
