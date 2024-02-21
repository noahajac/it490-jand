<?php

/**
 * Contains the logout frontend page.
 */

namespace JAND\Frontend;

require_once(__DIR__ . '/common/autoload/autoload.inc.php');
\JAND\Common\Autoload\Autoload::register();

/** Logout frontend page. */
abstract class Logout
{
  /** Performs logout and echoes HTML on error. */
  static function logout()
  {
    // Technically this can error, but it shouldn't ever happen.
    if (\JAND\Frontend\Utilities\SessionManager::logout()) {
      header('Location: index.php');
      exit();
    }
?>

    <!DOCTYPE html>
    <html lang="en">

    <head>
      <?= Elements\Head::head(); ?>
    </head>

    <body>
      <?= Elements\Nav::nav(); ?>
      <main>
        <h1 class="error">Error logging out! Please contact site administrator.</h1>
      </main>
      <?= Elements\Footer::footer(); ?>
    </body>

    </html>

<?php
  }
}

Logout::logout();
