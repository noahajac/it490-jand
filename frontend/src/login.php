<?php

namespace JAND\Frontend;

require_once(__DIR__ . '/common/autoload/autoload.inc.php');
\JAND\Common\Autoload\Autoload::register();


$error;
$session = Utilities\SessionManager::getSession();

if ($session) { // User already has a valid session.
  header('Location: index.php');
  exit();
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  $email = filter_input(INPUT_POST, 'email', FILTER_VALIDATE_EMAIL);
  $password = filter_input(INPUT_POST, 'password');

  $session = Utilities\SessionManager::login($email, password_hash($password, PASSWORD_DEFAULT));

  if ($session) {
    header('Location: index.php');
    exit();
  } else {
    $error = 'Incorrect username or password.';
  }
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
    <?php if (isset($error)) { ?>
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
