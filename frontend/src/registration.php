<?php

namespace JAND\Frontend;

require_once(__DIR__ . '/common/autoload/autoload.inc.php');
\JAND\Common\Autoload\Autoload::register();

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  $email = filter_input(INPUT_POST, 'email', FILTER_VALIDATE_EMAIL);
  $password = filter_input(INPUT_POST, 'password');
  $firstName = filter_input(INPUT_POST, 'first_name');
  $lastName - filter_input(INPUT_POST, 'last_name');



  function attemptRegistration($email, $password, $firstName, $lastName) {
    $client = new \JAND\Common\RabbitMq\RabbitMqClient(__DIR__ . '/rabbitmq.ini', 'db-frontend_frontend.client');
    $request = new \JAND\Common\Messages\Frontend\RegisterRequest($email, password_hash($password, PASSWORD_DEFAULT), $firstName, $lastName);
    $response = $request->sendRequest($client);
    if ($response instanceof \JAND\Common\Messages\Frontend\RegisterResponse) {
      if ($response->getResult()) {
        return $response;
      }
    } else {
      return false;
    }
  }

  try {
        $result = attemptRegistration($email, $password, $firstName, $lastName);

        if ($result && $result->getResult()) {
            setcookie('SESSION', $result->getSessionToken(), [
                'expires' => $result->getExpiration(),
                'path' => '/',
                'domain' => $_SERVER['SERVER_NAME'],
                'secure' => true, // Ensures cookies are sent over HTTPS
 		 !$config['dev_mode']['enabled'], // Only make secure if dev mode is disabled.
                'httponly' => true, // Prevents JavaScript access to the session cookie
                'samesite' => 'Lax' // Mitigates CSRF attacks
            ]);
            echo 'Registration successful.';
	    
            // Consider redirecting the user to a different page upon successful login
        } else {
            echo 'Invalid input.';
        }
    } catch (\Throwable $error) {
        echo 'An error has occurred.';
        exit();
  }
  
}

?>
<!DOCTYPE html>
<html>
  <head>
    <title>JAND Travel - Registration</title>
  </head>
  <body>
    <h1>Create your account</h1>
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
          <th><label for="first_name">First Name:</label></th>
          <td><input type="first_name" name="first_name" id="first_name" required></td>
        </tr>

        <tr>
          <th><label for="last_name">Last Name:</label></th>
          <td><input type="last_name" name="last_name" id="last_name" required></td>
        </tr>

        <tr>
          <td colspan="2"><input type="submit" value="Register"></td>
        </tr>
      </table> 
    </form>
  </body>
</html>
