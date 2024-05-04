<?php
/**
 * Contains the login frontend page.
 *
 * @package JAND\Frontend\Login\Includes\Login
 */

namespace JAND\Frontend\Login\Includes;

/**
 * Login frontend page.
 */
abstract class Login
{

    /**
     * User session object.
     *
     * @var false|\JAND\Common\Session $session Session object, or false if there is none.
     */
    private static false|\JAND\Common\Session $session;

    /**
     * Array of errors to show.
     *
     * @var string[] $errors Array of errors.
     */
    private static array $errors = [];


    /**
     * Performs login form logic.
     *
     * @return void
     */
    private static function processLogin()
    {
        try {
            static::$session = \JAND\Frontend\Includes\SessionManager::getSession();

            if (static::$session) {
                // User already has a valid session.
                header('Location: /landing');
                exit();
            }

            if ($_SERVER['REQUEST_METHOD'] === 'POST') {
                $email    = filter_input(INPUT_POST, 'email', FILTER_VALIDATE_EMAIL);
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

                static::$session = \JAND\Frontend\Includes\SessionManager::login($email, $password);

                if (static::$session) {
                    header('Location: /landing');
                    exit();
                } else {
                    array_push(static::$errors, 'Incorrect username or password.');
                }
            }//end if
        } catch (\Exception $e) {
            // Log the error here
            error_log('Error in processLogin: '.$e->getMessage(), 0);
            // Display a generic error message or handle the error accordingly
            array_push(static::$errors, 'An error occurred while processing the login.');
        }//end try

    }//end processLogin()


    /**
     * Echoes login page.
     *
     * @return void
     */
    public static function echoLogin()
    {
        self::processLogin();
        ?>
    <!DOCTYPE html>
    <html lang="en">

    <head>
        <?php echo \JAND\Frontend\Includes\Elements\Head::echoHead(); ?>
    </head>

    <body>
        <?php echo \JAND\Frontend\Includes\Elements\Nav::echoNav(); ?>
      <main>
        <?php foreach (static::$errors as $error) { ?>
          <p class="error"><?php echo $error; ?></p>
        <?php } ?>
        <div class="initial-ctr">
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
        </div>
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
    </body>

    </html>
        <?php

    }//end echoLogin()


}//end class
