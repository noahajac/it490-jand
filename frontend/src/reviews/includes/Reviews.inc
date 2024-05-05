<?php
/**
 * Contains frontend reviews page.
 *
 * @package JAND\Frontend\Reviews\Includes\Reviews
 */

namespace JAND\Frontend\Reviews\Includes;

use JAND\Common\Trips\Airline;
use JAND\Common\Trips\AirlineReview;
use JAND\Common\Trips\Hotel;
use JAND\Common\Trips\HotelReview;
use JAND\Common\Trips\Poi;
use JAND\Common\Trips\PoiReview;
use JAND\Frontend\Includes\LogSender;

/**
 * Frontend reviews page.
 */
abstract class Reviews
{


    /**
     * Echoes main reviews page.
     *
     * @param AirlineReview[]|HotelReview[]|PoiReview[] $reviews Reviews.
     * @param AirlineReview|HotelReview|PoiReview       $own     User's own review.
     * @param string[]                                  $errors  Errors to show on form.
     *
     * @return void
     */
    private static function echoReviews(array $reviews, mixed $own, array $errors=[])
    {
        ?>

    <!DOCTYPE html>
    <html lang="en">

    <head>
        <?php echo \JAND\Frontend\Includes\Elements\Head::echoHead(); ?>
        <link rel="stylesheet" href="styles/reviews.css">
    </head>

    <body>
        <?php echo \JAND\Frontend\Includes\Elements\Nav::echoNav(); ?>
      <main>
        <h1>Reviews</h1>
        <div class="review-container">
        <?php
        if (count($reviews) > 0) {
            ?>
            <h3>
            <?php
            if ($reviews[0] instanceof AirlineReview) {
                echo $reviews[0]->getAirline()->getName();
            } else if ($reviews[0] instanceof HotelReview) {
                echo $reviews[0]->getHotel()->getName();
            } else {
                echo $reviews[0]->getPoi()->getName();
            }
            ?>
            </h3>
            
        <div class="review overall-rating">
            <?php
                $adder = 0;
            foreach ($reviews as &$review) {
                $adder = ($adder + $review->getRating());
            }

            $average = ($adder / count($reviews));
            ?>
            <p class=>Overall Rating: <?= $average; ?></p>
        </div>
            <?php
            foreach ($reviews as &$review) {
                ?>
        <div class="review">
            <p class="rating">Rating: <?= $review->getRating(); ?></p>
            <p class="text-review">Review: <?= htmlspecialchars($review->getComment()); ?></p>
        </div>
                <?php
            }
            ?>

        
        <?php } else { ?>
            <h2>No reviews found.</h2>
            <?php
        }//end if
        ?>
        <div class="input-review-container">
        <div class="input-review">
            <h3>Write a Review</h3>
            <?php foreach ($errors as $error) { ?>
                <p class="error"><?php echo $error; ?></p>
            <?php } ?>
            <form name="input-review" id="input-review" action="#" method="post">
                <label for="input-rating">Rating:</label>
                <select name="input-rating" id="input-rating">
                    <option value="5" 
                    <?php
                    if (isset($own) && $own->getRating() === 5) {
                        echo 'selected';
                    }
                    ?>
                    >5</option>
                    <option value="4"
                    <?php
                    if (isset($own) && $own->getRating() === 4) {
                        echo 'selected';
                    }
                    ?>
                    >4</option>
                    <option value="3"
                    <?php
                    if (isset($own) && $own->getRating() === 3) {
                        echo 'selected';
                    }
                    ?>
                    >3</option>
                    <option value="2"
                    <?php
                    if (isset($own) && $own->getRating() === 2) {
                        echo 'selected';
                    }
                    ?>
                    >2</option>
                    <option value="1"
                    <?php
                    if (isset($own) && $own->getRating() === 1) {
                        echo 'selected';
                    }
                    ?>
                    >1</option>
                </select>
                <br>    
                <label for="input-text-review">
                    <p class="input-text-review">Write your review here:</p>
                    <textarea name="text-review" rows="10" cols="60">
<?php // phpcs:ignore Generic.WhiteSpace.ScopeIndent.Incorrect
        if (isset($own)) {
            echo htmlspecialchars($own->getComment());
        }

        // phpcs:ignore Squiz.PHP.EmbeddedPhp.ContentAfterEnd 
        ?></textarea>
        
                    <br>
                <div class="input-btn">
                <input type="submit" value="Submit" name="submit">
                </div>
            </form>
            <form method="post">
            <div class="input-btn">
            <button id="delete" name="delete" value="on" type="submit">Delete this Review</button>
            </div>
        </form>
        </div>
        </div>
    </div>
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
    </body>

    </html>
        <?php

    }//end echoReviews()


    /**
     * Starts review page.
     *
     * @return void
     */
    public static function processReviews()
    {
        LogSender::sendLog('Received a request for the reviews page.');

        $type = filter_input(INPUT_GET, 'type');
        $key  = filter_input(INPUT_GET, 'key');

        $session = \JAND\Frontend\Includes\SessionManager::getSession();

        if (!$session) {
            http_response_code(401);
            exit();
        }

        $errorMsgs = [];

        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            $rating  = filter_input(
                INPUT_POST,
                'input-rating',
                FILTER_VALIDATE_INT,
                [
                    'options' => [
                        'min_range' => 1,
                        'max_range' => 5,
                    ],
                ]
            );
            $comment = filter_input(INPUT_POST, 'text-review', FILTER_SANITIZE_FULL_SPECIAL_CHARS);
            $delete  = filter_input(INPUT_POST, 'delete', FILTER_VALIDATE_BOOL);

            if ($delete) {
                if ($type === 'airline') {
                    $request = new \JAND\Common\Messages\Frontend\DeleteReviewRequest(
                        $session->getSessionToken(),
                        new AirlineReview(
                            null,
                            5,
                            '',
                            new Airline($key, null)
                        )
                    );
                } else if ($type === 'hotel') {
                    $request = new \JAND\Common\Messages\Frontend\DeleteReviewRequest(
                        $session->getSessionToken(),
                        new HotelReview(
                            null,
                            5,
                            '',
                            new Hotel($key, null, null, null)
                        )
                    );
                } else {
                    $request = new \JAND\Common\Messages\Frontend\DeleteReviewRequest(
                        $session->getSessionToken(),
                        new PoiReview(
                            null,
                            5,
                            '',
                            new Poi($key, null, [], null)
                        )
                    );
                }//end if

                \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);
            } else {
                if (empty($comment)) {
                    $comment = '';
                }

                if (empty($rating)) {
                    array_push($errorMsgs, 'You must supply a valid rating.');
                }

                if (count($errorMsgs) < 1) {
                    if ($type === 'airline') {
                        $request = new \JAND\Common\Messages\Frontend\CreateReviewRequest(
                            $session->getSessionToken(),
                            new AirlineReview(
                                null,
                                $rating,
                                $comment,
                                new Airline($key, null)
                            )
                        );
                    } else if ($type === 'hotel') {
                        $request = new \JAND\Common\Messages\Frontend\CreateReviewRequest(
                            $session->getSessionToken(),
                            new HotelReview(
                                null,
                                $rating,
                                $comment,
                                new Hotel($key, null, null, null)
                            )
                        );
                    } else {
                        $request = new \JAND\Common\Messages\Frontend\CreateReviewRequest(
                            $session->getSessionToken(),
                            new PoiReview(
                                null,
                                $rating,
                                $comment,
                                new Poi($key, null, [], null)
                            )
                        );
                    }//end if

                    \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);
                }//end if
            }//end if
        }//end if

        if ($type === 'airline') {
            $request = new \JAND\Common\Messages\Frontend\GetAirlineReviewsRequest(
                $session->getSessionToken(),
                new Airline($key, null)
            );
            /**
             * Reviews from DB.
             *
             * @var \JAND\Common\Messages\Frontend\GetReviewsResponse $response Response.
             */
            $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);
        } else if ($type === 'hotel') {
            $request = new \JAND\Common\Messages\Frontend\GetHotelReviewsRequest(
                $session->getSessionToken(),
                new Hotel($key, null, null, null)
            );
            /**
             * Reviews from DB.
             *
             * @var \JAND\Common\Messages\Frontend\GetReviewsResponse $response Response.
             */
            $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);
        } else {
            $request = new \JAND\Common\Messages\Frontend\GetPoiReviewsRequest(
                $session->getSessionToken(),
                new Poi($key, null, [], null)
            );
            /**
             * Reviews from DB.
             *
             * @var \JAND\Common\Messages\Frontend\GetReviewsResponse $response Response.
             */
            $response = \JAND\Frontend\Includes\RabbitClientManager::sendRequest($request);
        }//end if

        $reviews   = $response->getReviews();
        $ownReview = $response->getOwn();

        static::echoReviews($reviews, $ownReview, $errorMsgs);

    }//end processReviews()


}//end class