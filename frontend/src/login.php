<?php

/** Contains the login frontend page. */

namespace JAND\Frontend;

require_once(__DIR__ . '/common/autoload/autoload.inc.php');
\JAND\Common\Autoload\Autoload::register();

/** Login frontend page. */
abstract class Login
{
  /** @var false|\JAND\Common\Utilities\Session $session Session object, or false if there is none. */
  private static false|\JAND\Common\Utilities\Session $session;
  
  /**
   * @var string[] $errors Array of errors.
   */
  private static array $errors = [];

  /** Performs login form logic. */
  private static function processLogin()
  {
    static::$session = Utilities\SessionManager::getSession();

    if (static::$session) { // User already has a valid session.
      header('Location: index.php');
      exit();
    }

    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
      $email = filter_input(INPUT_POST, 'email', FILTER_VALIDATE_EMAIL);
      $password = filter_input(INPUT_POST, 'password');

      if (empty($email)) {
        array_push(static::$errors, 'Please enter your email address.');
      }
      if (empty($password)) {
        array_push(static::$errors, 'Please enter your password.');
      }

      // If there are any errors, go back to form.
      if (static::$errors) {
        return;
      }

      static::$session = Utilities\SessionManager::login($email, password_hash($password, PASSWORD_DEFAULT));

      if (static::$session) {
        header('Location: index.php');
        exit();
      } else {
        array_push(static::$errors, 'Incorrect username or password.');
      }
    }
  }
  /** Echoes login page. */
  static function login()
  {
    self::processLogin();
?>
    <!DOCTYPE html>
    <html lang="en">

    <head>
      <?= Elements\Head::head(); ?>
    </head>

    <body>
      <?= Elements\Nav::nav(); ?>
      <main>
        <?php foreach (static::$errors as $error) { ?>
          <p class="error"><?= $error; ?></p>
        <?php } ?>
        <h2>Login</h2>
        <form method="post">
          <table>
            <tr>
              <th><label for="email">Email:</label></th>
              <td><input type="email" name="email" id="email" required></td>
            </tr>

            <tr>
              <th><label for="password">Password:</label></th>
              <td><input type="password" name="password" id="password" required></td>
            </tr>

            <tr>
              <td colspan="2"><input type="submit" value="Log in"></td>
            </tr>
          </table>
        </form>
      </main>
      <?= Elements\Footer::footer(); ?>
    </body>

    </html>
<?php
  }
}

Login::login();
