<?php
/**
 * Contains the register frontend page.
 *
 * @package JAND\Frontend\Register\Includes\Register
 */

namespace JAND\Frontend\Register\Includes;

/**
 * Frontend register page.
 */
abstract class Register
{

    /**
     * Session object, error object, or false if nothing else.
     *
     * @var false|\JAND\Common\Session|\JAND\Common\Messages\Frontend\RegisterError $session
     */
    private static false|\JAND\Common\Session|\JAND\Common\Messages\Frontend\RegisterError $session;

    /**
     * Array of errors to show user.
     *
     * @var string[] Array of errors.
     */
    private static array $errors = [];


    /**
     * Performs registration logic.
     *
     * @return void
     */
    private static function processRegistration()
    {
        static::$session = \JAND\Frontend\Includes\SessionManager::getSession();

        if (static::$session) {
            // User already has a valid session.
            header('Location: /landing');
            exit();
        }

        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            $email     = filter_input(INPUT_POST, 'email', FILTER_VALIDATE_EMAIL);
            $password  = filter_input(
                INPUT_POST,
                'password',
                FILTER_CALLBACK,
                [
                    'options' => function (string $value) {
                        return (strlen($value) > 7) ? $value : false;
                    },
                ]
            );
            $firstName = filter_input(
                INPUT_POST,
                'first-name',
                FILTER_SANITIZE_SPECIAL_CHARS,
                ['flags' => (FILTER_FLAG_STRIP_LOW | FILTER_FLAG_STRIP_HIGH | FILTER_FLAG_STRIP_BACKTICK)]
            );
            $lastName  = filter_input(
                INPUT_POST,
                'last-name',
                FILTER_SANITIZE_SPECIAL_CHARS,
                ['flags' => (FILTER_FLAG_STRIP_LOW | FILTER_FLAG_STRIP_HIGH | FILTER_FLAG_STRIP_BACKTICK)]
            );

            if (empty($email)) {
                array_push(static::$errors, 'Please enter a valid email address.');
            }

            if (empty($firstName)) {
                array_push(static::$errors, 'Please enter your first name.');
            }

            if (empty($lastName)) {
                array_push(static::$errors, 'Please enter your last name.');
            }

            if (empty($password)) {
                array_push(static::$errors, 'Password must be at least 8 characters.');
            }

            // If there are any errors, go back to form.
            if (static::$errors) {
                return;
            }

            static::$session = \JAND\Frontend\Includes\SessionManager::register(
                $email,
                $password,
                $firstName,
                $lastName
            );

            if (static::$session instanceof \JAND\Common\Session) {
                header('Location: /landing');
                exit();
            } else if (static::$session instanceof \JAND\Common\Messages\Frontend\RegisterError) {
                array_push(static::$errors, static::$session->getMessage());
            } else {
                array_push(static::$errors, 'An error has occured while registering.');
            }
        }//end if

    }//end processRegistration()


    /**
     * Echoes registration page.
     *
     * @return void
     */
    public static function echoRegister()
    {
        static::processRegistration();
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
        <h2>Register new account</h2>
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
              <th><label for="first-name">First Name:</label></th>
              <td><input type="text" name="first-name" id="first-name" required></td>
            </tr>

            <tr>
              <th><label for="last-name">Last Name:</label></th>
              <td><input type="text" name="last-name" id="last-name" required></td>
            </tr>

            <tr>
              <td colspan="2"><input type="submit" value="Register"></td>
            </tr>
          </table>
        </form>
      </main>
        <?php echo \JAND\Frontend\Includes\Elements\Footer::echoFooter(); ?>
    </body>

    </html>

        <?php

    }//end echoRegister()


}//end class
