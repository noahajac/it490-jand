<?php
/**
 * Contains frontend reviews page.
 *
 * @package JAND\Frontend\Reviews\Includes\Reviews
 */

namespace JAND\Frontend\Reviews\Includes;

/**
 * Frontend reviews page.
 */
abstract class Reviews
{


    /**
     * Echoes main reviews page.
     *
     * @return void
     */
    public static function echoReviews()
    {
        ?>

    <!DOCTYPE html>
    <html lang="en">

    <head>
        <?php echo \JAND\Frontend\Includes\Elements\Head::echoHead(); ?>
        <title>JAND Travel - Reviews</title>
        <link rel="stylesheet" href="reviews.css">
        <style>
            main{
                margin: 0 auto;
                padding: 20px;
            }
            main h1{
                text-align: center;
            }
            .review-container{
                display: flex;
                flex-direction: column;
                padding: 60px;
                gap: 20px;
            }
            .review{
                border: 1px solid black;
                padding: 10px;
            }
            .overall-rating{
                font-size: 25px;
            }
            .input-review-container{
                display: flex;
                justify-content: center;
            }
            .input-review{
                padding: 10px;
           }
        </style>
    </head>

    <body>
        <?php echo \JAND\Frontend\Includes\Elements\Nav::echoNav(); ?>
      <main>
        <h1>Reviews</h1>
        <div class="review-container">
        <div class="review overall-rating">
            <p class=>Overall Rating: 4.67</p>
        </div>
        <div class="review">
            <p class="customer-name">Name: Rob Johnson</p>
            <p class="service">Service: Airline</p>
            <p class="company">Company Name: United Airlines</p>
            <p class="rating">Rating: 4</p>
            <p class="text-review">Review: Satisfactory service.</p>
        </div>
        <div class="review">
            <p class="customer-name">Name: James Hunt</p>
            <p class="service">Service: Hotel</p>
            <p class="company">Company Name: Hard Rock Hotel and Casino Atlantic City </p>
            <p class="rating">Rating: 5</p>
            <p class="text-review">Review: Amazing experience!</p>
        </div>
        <div class="review">
            <p class="customer-name">Name: Alice Smith</p>
            <p class="service">Service: Attraction</p>
            <p class="company">Company Name: Cape May County Park and Zoo</p>
            <p class="rating">Rating: 5</p>
            <p class="text-review">Review: Had a great time.</p>
        </div>
        </div>
        <div class="input-review-container">
        <div class="input-review">
            <h3>Write a Review</h3>
            <!--Example data. Can make a cascading dropdown menu with api data.-->
            <form name="input-review" id="input-review" action="#" method="post">
                <label for="input-service">Choose Service:</label>
                    <select name="service" id="service">
                        <option value="Airline">Airline</option>
                        <option value="Hotel">Hotel</option>
                        <option value="Attraction">Attraction</option>
                    </select>
                    <br>
                <label for="input-company">Choose Company Name:</label>
                    <select name="company" id="cars">
                        <option value="United-Airlines">United Airlines</option>
                        <option value="Hard-Rock">Hard Rock Hotel and Casino Atlantic City</option>
                        <option value="Cape-May">Cape May County Park and Zoo</option>
                    </select>
                    <br>
                <label for="input-rating">Rating:</label>
                <select name="input-rating" id="input-rating">
                    <option value="5">5</option>
                    <option value="4">4</option>
                    <option value="3">3</option>
                    <option value="2">2</option>
                    <option value="1">1</option>
                </select>
                <br>    
                <label for="input-text-review">
                    <p class="input-text-review">Write your review here:</p>
                    <textarea name="text-review" rows="10" cols="60"></textarea>
                    <br>
                <input type="submit" value="Submit" name="submit">
            </form>
        </div>
        </div>
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
    </body>

    </html>
        <?php

    }//end echoReviews()


}//end class