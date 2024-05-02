<?php
/**
 * Contains frontend main landing page.
 *
 * @package JAND\Frontend\Landing\Includes\Landing
 */

namespace JAND\Frontend\Landing\Includes;

use JAND\Common\Trips\Poi;

/**
 * Main landing page.
 */
abstract class Landing
{


    /**
     * Echoes main landing page.
     *
     * @return void
     */
    public static function echoLanding()
    {
      try{
        ?>

    <!DOCTYPE html>
    <html lang="en">

    <head>
        <?php echo \JAND\Frontend\Includes\Elements\Head::echoHead(); ?>
        <link rel="stylesheet" href="styles/landing.css">
    </head>

    <body>
        <?php echo \JAND\Frontend\Includes\Elements\Nav::echoNav(); ?>
      <main>
        <h1>Welcome to JAND Travel</h1>
        <?php
        $session = \JAND\Frontend\Includes\SessionManager::getSession();

        if ($session) {
            $request = new \JAND\Common\Messages\Frontend\GetRecommendationsRequest(
                $session->getSessionToken(),
            );
            /**
             * Recommendations from DB.
             *
             * @var \JAND\Common\Messages\Frontend\GetRecommendationsResponse $response Reccs from DB.
             */
            $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);

            if (count($response->getPois()) > 0) {
                ?>
        <div class="rec-container">
        <div class="rec">
        <div class="rec">
            <h3 class="rec-heading">Recommendations for You</h3>
            <p>Based off of reviews and your preferences.</p>
            <table>
            <?php
                $index = 0;
                foreach ($response->getPois() as &$poi) {
                $hide = filter_input(INPUT_POST, 'hide'.strval($index), FILTER_VALIDATE_BOOL);
                if (!$hide){ 
            ?>
                    <tr>
                    <td><strong><?= $poi->getName(); ?></strong></td>
                    <td>
                        <a href="/flight-search?to=<?= $poi->getCity()->getCode(); ?>"
                        ><?= $poi->getCity()->getName().', '.$poi->getCity()->getCountryCode(); ?></a>
                    </td>
                    <td>
                             <a href="/reviews?type=poi&key=<?= $poi->getPoiId(); ?>"
                                        >Reviews</a>
                                    </td>
                        <td>
                        <form method="post" action="">
                        <button id="hide<?php echo $index?>" name="hide<?php echo $index?>" value="on" type="submit">Hide</button>
                        </form>
                    </td>
                </tr>
                <tr>
                            <th colspan="4">
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
                            </th>
                        </tr>
                        
                    <?php
                        }// end if statement
                else{
                        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
                                $request = new \JAND\Common\Messages\Frontend\GetRecommendationsRequest(
                                $session->getSessionToken(),
                                new Poi($key, null, [], null)
                        );

                        $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);
                        }
                }
                $index++;
                }//end foreach
                ?>
                </table>
        </div>
        </div>
                <?php
            } else {
                ?>
                                <p>No recommendations for you at this time.</p>
                <?php
            }//end if
        }//end if
        ?>
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
    </body>

    </html>
        <?php
}  catch (/Exception $e){
  // Log the error here
        error_log('Error in echoLanding: ' . $e->getMessage(), 0);

        echo '<p>An error occurred while loading the landing page.</p>';

}
    }//end echoLanding()


}//end class
