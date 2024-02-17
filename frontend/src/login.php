<?php

require_once('includes/common/rabbitMQLib.inc.php');
require_once('includes/common/messages.inc.php');
require_once('includes/common/parse_config.inc.php');

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  $email = filter_input(INPUT_POST, 'email', FILTER_VALIDATE_EMAIL);
  $password = filter_input(INPUT_POST, 'password');

  function attemptLogin($email, $password) {
    $client = new rabbitMQClient("includes/rabbitmq.ini");
    $request = new JAND\Frontend\LoginRequest($email, password_hash($password, PASSWORD_DEFAULT));
    $response = $request->sendRequest($client);
    if ($response instanceof JAND\Frontend\LoginResponse) {
      if ($response->getResult()) {
        return $response;
      }
    } else {
      return false;
    }
  }

  try {
        $result = attemptLogin($email, $password);

        if ($result && $result->getResult()) {
            // Assuming get_result() checks if login was successful and get_session_token() exists
            setcookie('SESSION', $result->getSessionToken(), [
                'expires' => $result->getExpiration(),
                'path' => '/',
                'domain' => $_SERVER['SERVER_NAME'],
                'secure' => true, // Ensures cookies are sent over HTTPS
 		 !$config['dev_mode']['enabled'], // Only make secure if dev mode is disabled.
                'httponly' => true, // Prevents JavaScript access to the session cookie
                'samesite' => 'Lax' // Mitigates CSRF attacks
            ]);
            echo 'Login successful.';
            // Consider redirecting the user to a different page upon successful login
        } else {
            echo 'Incorrect username or password.';
        }
    } catch (Throwable $error) {
        echo 'An error has occurred.';
        exit();
  }
  
}

?>
<!DOCTYPE html>
<html>
  <head>
    <title>JAND Travel- Login</title>
  </head>
  <body>
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
          <td colspan="2"><input type="submit"></td>
        </tr>
      </table>      
    </form>
  </body>
</html>