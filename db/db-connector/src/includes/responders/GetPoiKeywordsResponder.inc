<?php
/**
 * Contains the responder for a get POI keywords request.
 *
 * @package JAND\DbConnector\Includes\Responders\GetPoiKeywordsResponder
 */

namespace JAND\DbConnector\Includes\Responders;

/**
 * Responds to get user trip requests.
 */
abstract class GetPoiKeywordsResponder
{


    /**
     * Responds to a get user trips request.
     *
     * @param \JAND\Common\Messages\Frontend\GetPoiKeywordsRequest $request User trips request.
     * @param \PDO                                                 $pdo     PDO instance.
     *
     * @return \JAND\Common\Messages\Frontend\GetPoiKeywordsResponse Response to request.
     */
    public static function respondToRequest(\JAND\Common\Messages\Frontend\GetPoiKeywordsRequest $request, \PDO $pdo)
    {
        $stmt = $pdo->prepare(
            'SELECT DISTINCT keyword FROM poi_keywords'
        );
        $stmt->execute();
        $dbResults = $stmt->fetchAll();
        $stmt->closeCursor();

        $keywords = [];

        foreach ($dbResults as &$result) {
            array_push(
                $keywords,
                $result['keyword']
            );
        }

        return new \JAND\Common\Messages\Frontend\GetPoiKeywordsResponse($keywords);

    }//end respondToRequest()


}//end class
