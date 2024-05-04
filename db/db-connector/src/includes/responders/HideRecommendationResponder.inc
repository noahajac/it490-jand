<?php
/**
 * Contains the responder for a hide recommendation request.
 *
 * @package JAND\DbConnector\Includes\Responders\HideRecommendationResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use JAND\Common\Messages\Frontend\HideRecommendationRequest;

/**
 * Responds to hide recommendation requests.
 */
abstract class HideRecommendationResponder
{


    /**
     * Responds to a delete review request.
     *
     * @param HideRecommendationRequest $request Hide recommendation request.
     * @param \PDO                      $pdo     PDO instance.
     *
     * @return HideRecommendationResponse Response to request.
     */
    public static function respondToRequest(HideRecommendationRequest $request, \PDO $pdo)
    {
        $sessionToken = $request->getSessionToken();
        $poiId        = $request->getPoiId();

        $stmt = $pdo->prepare(
            'INSERT INTO hide_poi VALUES 
(:poiId, (SELECT user_id FROM sessions WHERE session_token=:sessionToken)) 
ON DUPLICATE KEY UPDATE poi_id=:poiId'
        );
        $stmt->execute(
            [
                'sessionToken' => $sessionToken,
                'poiId'        => $poiId,
            ]
        );

        $stmt->closeCursor();

        return new \JAND\Common\Messages\Frontend\HideRecommendationResponse();

    }//end respondToRequest()


}//end class
