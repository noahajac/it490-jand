
namespace JAND\Frontend\Landing\Includes;

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
        try {
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

                        // Attempt to fetch recommendations
                        $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);

                        if (count($response->getPois()) > 0) {
                            ?>
                            <div class="rec-container">
                                <!-- Recommendations display code here -->
                            </div>
                            <?php
                        } else {
                            ?>
                            <p>No recommendations for you at this time.</p>
                            <?php
                        }
                    }
                    ?>
                </main>
                <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
            </body>
            </html>
            <?php
        } catch (\Exception $e) {
            // Display or handle the error as needed
            echo 'An error occurred. Please try again later.';
        }
    }
}
