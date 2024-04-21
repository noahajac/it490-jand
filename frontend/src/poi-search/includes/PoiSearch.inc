<?php
/**
 * Contains frontend POI search page.
 *
 * @package JAND\Frontend\PoiSearch\Includes\PoiSearch
 */

namespace JAND\Frontend\PoiSearch\Includes;

/**
 * POI search page.
 */
abstract class PoiSearch
{


    /**
     * Echoes POI search page.
     *
     * @param String[]                 $errors Errors to show.
     * @param \JAND\Common\Trips\Poi[] $pois   POIs to show.
     *
     * @return void
     */
    private static function echoPoiSearch(array $errors=[], array $pois=[])
    {
        ?>

        <!DOCTYPE html>
        <html lang="en">

        <head>
            <?php echo \JAND\Frontend\Includes\Elements\Head::echoHead(); ?>
        </head>
            
        <body>
        <?php echo \JAND\Frontend\Includes\Elements\Nav::echoNav(); ?>
        <main>
            <?php
            if (count($pois) > 0) {
                foreach ($pois as &$poi) {
                    ?>
                    <div class="flight-result">
                    <table class="table-borders">
                        <tr>
                            <th><?= $poi->getName(); ?></th>
                        </tr>
                        <tr>
                            <td>
                            <?php
                            $onTag = 1;
                            foreach ($poi->getTags() as &$tag) {
                                if ($onTag < count($poi->getTags())) {
                                    echo ucwords($tag).', ';
                                } else {
                                    echo ucwords($tag);
                                }

                                $onTag++;
                            }
                            ?>
                            </td>
                        </tr>
                        <tr>
                        <td>
                             <a href="/reviews?type=poi&key=<?= $poi->getPoiId(); ?>"
                                        >Reviews</a>
                                    </td>
                        </tr>
                    </table>
                    </div>
                    <?php
                }//end foreach
            } else {
                ?>
            <div class="main-container">
        <div class="booking-form">
            
            <h2 class="title-form">Search for Attractions</h2>
            
                <?php foreach ($errors as $error) { ?>
          <p class="error"><?php echo $error; ?></p>
                <?php } ?>

            <form method="post">
                <div class="input-group">
                    <label for="destination">Destination:</label>
                    <input type="text" id="destination-display" placeholder="Going To?" required> 
                    <input type="hidden" id="destination" name="destination"> 
                </div>

                <div class="input-group">
                    <label for="type">Type:</label>
                    <select id="attraction-type" name="attraction-type">
                        <option value="">All</option>
                        <?php
                        $request = new \JAND\Common\Messages\Frontend\GetPoiKeywordsRequest();
                        /**
                         * Keywords from DB.
                         *
                         * @var \JAND\Common\Messages\Frontend\GetPoiKeywordsResponse $response Response.
                         */
                        $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);

                        foreach ($response->getKeywords() as &$keyword) {
                            ?>
                                <option value="<?= $keyword; ?>"><?= ucwords($keyword); ?></option>
                            <?php
                        }
                        ?>
                    </select>
                </div>

            
                <input type="submit" id="search-submit" value="Search">
            
            </form>
            </div>
        </div>
                <?php
            }//end if
            ?>
        </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
        <script src="./scripts/city-autocomplete.js"></script>
        </body>
        </html>

        <?php

    }//end echoPoiSearch()


    /**
     * Runs the POI search page.
     *
     * @return void
     */
    public static function processPoiSearch()
    {
        $session = \JAND\Frontend\Includes\SessionManager::getSession();

        if (!$session) {
            http_response_code(401);
            exit();
        }

        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            $errorMsgs = [];

            $destination = filter_input(INPUT_POST, 'destination', FILTER_SANITIZE_FULL_SPECIAL_CHARS);

            $attractionType = filter_input(INPUT_POST, 'attraction-type');

            $request  = new \JAND\Common\Messages\Shared\AirportCitySearchRequest(
                $destination
            );
            $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);

            $destinationCity = $response->checkCode(strtoupper($destination));
            if (!$destinationCity) {
                array_push($errorMsgs, 'Destination is not valid.');
            }

            if (count($errorMsgs) > 0) {
                static::echoPoiSearch($errorMsgs);
                exit();
            }

            $request = new \JAND\Common\Messages\Shared\PoiSearchRequest(
                $destinationCity
            );

            /**
             * Poi itinerary search response.
             *
             * @var \JAND\Common\Messages\Shared\PoiSearchResponse $response Search response.
             */
            $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);

            $pois = [];
            if (!empty($attractionType)) {
                foreach ($response->getPois() as &$poi) {
                    foreach ($poi->getTags() as &$tag) {
                        if ($tag === $attractionType) {
                            array_push($pois, $poi);
                            break;
                        }
                    }
                }
            } else {
                $pois = $response->getPois();
            }

            if (count($pois) < 1) {
                static::echoPoiSearch(['No attractions found.']);
            } else {
                static::echoPoiSearch([], $pois);
            }
        } else {
            static::echoPoiSearch();
        }//end if

    }//end processPoiSearch()


}//end class
