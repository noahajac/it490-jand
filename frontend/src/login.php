<?php

require_once('includes/common/rabbitMQLib.inc.php');
require_once('includes/common/types.inc.php');

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  $email = filter_input(INPUT_POST, 'email', FILTER_VALIDATE_EMAIL);
  $password = filter_input(INPUT_POST, 'password');

  function attemptLogin($email, $password) {
    $client = new rabbitMQClient("includes/rabbitmq.ini");
    $request = new JAND\FrontendRequest(JAND\FrontendRequests::login);
    $request->set_email($email);
    $request->set_password($password);
    echo(serialize($request));
    $response = $client->send_request(serialize($request), 'application/php-serialized');
    echo($response);
  }

  attemptLogin($email, $password);
}

?>
<!DOCTYPE html>
<html>
  <head>
    <title>JAND Travel</title>
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
