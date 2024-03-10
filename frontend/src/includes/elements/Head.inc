<?php
/**
 * Contains the head element contents used throughout the site.
 *
 * @package JAND\Frontend\Includes\Elements\Head
 */

namespace JAND\Frontend\Includes\Elements;

/**
 * Head element contents.
 */
abstract class Head
{


    /**
     * Echoes the head element content HTML.
     *
     * @return void
     */
    public static function echoHead()
    {
        ?>
    <meta charset="utf-8">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" 
    rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" 
    crossorigin="anonymous">
    <link rel="stylesheet" href="/styles/styles.css">
    <title>JAND Travel</title>
        <?php

    }//end echoHead()


}//end class
