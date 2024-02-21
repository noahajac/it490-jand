<?php

/** Contains the head element contents used throughout the site. */

namespace JAND\Frontend\Elements;

/** Head element contents. */
abstract class Head
{
  /** Echoes the head element content HTML. */
  static function head()
  {
?>
    <meta charset="utf-8">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <link rel="stylesheet" href="styles.css">
    <title>JAND Travel</title>
<?php
  }
}
