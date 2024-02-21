<?php

/** Contains the nav bar element used throughout the site. */

namespace JAND\Frontend\Elements;

/** Navigation bar. */
abstract class Nav
{
  /** Echoes navigation bar HTML. */
  static function nav()
  {
?>
    <nav class="navbar navbar-expand-lg navbar-light">
      <div class="container-fluid">
        <a class="navbar-brand" href="index.php">JAND Travel</a>
        <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNavDropdown">
          <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="navbarNavDropdown">
          <ul class="navbar-nav">
            <li class="nav-item">
              <a class="nav-link active" href="index.php">Home</a>
            </li>
            <li class="nav-item dropdown">
              <?php $session = \JAND\Frontend\Utilities\SessionManager::getSession(); ?>
              <a class="nav-link active dropdown-toggle" id="navbarDropdownMenuLink" role="button" data-bs-toggle="dropdown"> <?php
                                                                                                                              if ($session) {
                                                                                                                                echo (htmlspecialchars($session->getFirstName() . ' ' . $session->getLastName()));
                                                                                                                              } else { ?>
                  Account <?php } ?></a>
              <ul class="dropdown-menu"><?php
                                        if ($session) { ?>
                  <li><a class="dropdown-item" href="logout.php">Logout</a></li>
                <?php } else {
                ?>
                  <li><a class="dropdown-item" href="login.php">Login</a></li>
                  <li><a class="dropdown-item" href="register.php">Register</a></li>
                <?php } ?>
              </ul>
            </li>
          </ul>
        </div>
      </div>
    </nav>
<?php
  }
}
