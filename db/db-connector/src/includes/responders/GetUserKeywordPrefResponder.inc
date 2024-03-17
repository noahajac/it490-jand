<?php
/**
 * Contains the responder for a get user keyword prefs request.
 *
 * @package JAND\DbConnector\Includes\Responders\GetUserKeywordPrefResponder
 */

namespace JAND\DbConnector\Includes\Responders;

/**
 * Responds to get user keyword prefs requests.
 */
abstract class GetUserKeywordPrefResponder
{


    /**
     * Responds to a get user keyword prefs request.
     *
     * @param \JAND\Common\Messages\Frontend\GetUserKeywordPrefRequest $request User keyword pref request.
     * @param \PDO                                                     $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\GetUserKeywordPrefResponse Response to request.
     */
    public static function respondToRequest(
        \JAND\Common\Messages\Frontend\GetUserKeywordPrefRequest $request,
        \PDO $pdo
    ) {
        $sessionToken = $request->getSessionToken();

        $stmt = $pdo->prepare(
            'SELECT * FROM 
user_keyword_preferences as p, sessions as s WHERE p.user_id=s.user_id AND 
s.session_token = :sessionToken'
        );
        $stmt->execute(['sessionToken' => $sessionToken]);
        $dbResults = $stmt->fetchAll();
        $stmt->closeCursor();

        $keywords = [];

        foreach ($dbResults as &$result) {
            array_push(
                $keywords,
                $result['keyword']
            );
        }

        return new \JAND\Common\Messages\Frontend\GetUserKeywordPrefResponse($keywords);

    }//end respondToRequest()


}//end class
