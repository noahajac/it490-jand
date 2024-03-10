<?php
/**
 * Contains last elements of body for the site.
 *
 * @package JAND\Frontend\Includes\Elements\Footer
 */

namespace JAND\Frontend\Includes\Elements;

/**
 * Footer for site, last elements within body.
 */
abstract class Footer
{


    /**
     * Echoes site footer HTML.
     *
     * @return void
     */
    public static function echoFooter()
    {
        ?>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" 
    integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" 
    crossorigin="anonymous"></script>
        <?php

    }//end echoFooter()


}//end class
