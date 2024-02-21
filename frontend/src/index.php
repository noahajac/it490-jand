<?php

/** Contains frontend main landing page. */

namespace JAND\Frontend;

require_once(__DIR__ . '/common/autoload/autoload.inc.php');
\JAND\Common\Autoload\Autoload::register();

/** Main landing page. */
abstract class Index
{
  /** Echoes main landing page. */
  static function index()
  {
?>

    <!DOCTYPE html>
    <html lang="en">

    <head>
      <?= Elements\Head::head(); ?>
    </head>

    <body>
      <?= Elements\Nav::nav(); ?>
      <main>
        <h1>Welcome to JAND Travel</h1>
      </main>
      <?= Elements\Footer::footer(); ?>
    </body>

    </html>
<?php
  }
}
