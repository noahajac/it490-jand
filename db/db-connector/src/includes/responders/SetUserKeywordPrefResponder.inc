<?php
/**
 * Contains the responder for a set user keyword prefs request.
 *
 * @package JAND\DbConnector\Includes\Responders\SetUserKeywordPrefResponder
 */

namespace JAND\DbConnector\Includes\Responders;

use JAND\Common\Messages\Frontend\GetPoiKeywordsRequest;

/**
 * Responds to set user keyword prefs requests.
 */
abstract class SetUserKeywordPrefResponder
{


    /**
     * Responds to a set user keyword prefs request.
     *
     * @param \JAND\Common\Messages\Frontend\SetUserKeywordPrefRequest $request User request.
     * @param \PDO                                                     $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\SetUserKeywordPrefResponse Response to request.
     */
    public static function respondToRequest(
        \JAND\Common\Messages\Frontend\SetUserKeywordPrefRequest $request,
        \PDO $pdo
    ) {
        $sessionToken = $request->getSessionToken();

        // First, clear existing.
        $stmt = $pdo->prepare(
            'DELETE FROM user_keyword_preferences WHERE 
user_id=(SELECT user_id FROM sessions WHERE session_token=:sessionToken)'
        );
        $stmt->execute(
            ['sessionToken' => $sessionToken]
        );
        $stmt->closeCursor();

        $allowedKeywords = GetPoiKeywordsResponder::respondToRequest(new GetPoiKeywordsRequest(), $pdo)->getKeywords();

        foreach ($request->getKeywords() as &$keyword) {
            echo $keyword;
            if (!in_array($keyword, $allowedKeywords, true)) {
                continue;
            }

            $stmt = $pdo->prepare(
                'INSERT INTO user_keyword_preferences VALUES 
    ((SELECT user_id FROM sessions WHERE session_token=:sessionToken), :keyword)'
            );
            $stmt->execute(
                [
                    'sessionToken' => $sessionToken,
                    'keyword'      => $keyword,
                ]
            );
            $stmt->closeCursor();
        }

        return new \JAND\Common\Messages\Frontend\SetUserKeywordPrefResponse();

    }//end respondToRequest()


}//end class
