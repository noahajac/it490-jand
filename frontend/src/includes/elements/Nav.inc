<?php
/**
 * Contains the nav bar element used throughout the site.
 *
 * @package JAND\Frontend\Includes\Elements\Nav
 */

namespace JAND\Frontend\Includes\Elements;

/**
 * Navigation bar.
 */
abstract class Nav
{


    /**
     * Echoes navigation bar HTML.
     *
     * @return void
     */
    public static function echoNav()
    {
        ?>
    <nav class="navbar navbar-expand-lg navbar-light">
      <div class="container-fluid">
        <a class="navbar-brand" href="/landing">JAND Travel</a>
        <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNavDropdown">
          <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="navbarNavDropdown">
          <ul class="navbar-nav">
            <li class="nav-item">
              <a class="nav-link active" href="/landing">Home</a>
            </li>
            <?php
            $session = \JAND\Frontend\Includes\SessionManager::getSession();
            if ($session) {
                ?>
            <li>
              <a class="nav-link active" href="/user-trips">My Trips</a>
            </li>
            <li>
              <a class="nav-link active" href="/flight-search">Search Flights</a>
            </li>
            <li>
              <a class="nav-link active" href="/hotel-search">Search Hotels</a>
            </li>
            <li>
              <a class="nav-link active" href="/poi-search">Search Attractions</a>
            </li>
            <li>
              <a class="nav-link active" href="/bookings">My Bookings</a>
            </li>
            <?php } ?>
            <li class="nav-item dropdown account-nav">
              <a class="nav-link active dropdown-toggle"
              id="navbarDropdownMenuLink" role="button" data-bs-toggle="dropdown"> 
              <?php
                if ($session) {
                    echo htmlspecialchars($session->getFirstName().' '.$session->getLastName());
                } else {
                    ?>
                  Account 
                <?php } ?></a>
              <ul class="dropdown-menu">
              <?php
                if ($session) {
                    ?>
                    <li>
                      <a class="dropdown-item" href="/user-preferences">Set User Preferences</a>
                  </li>
                  <li><a class="dropdown-item" href="/logout">Logout</a></li>
                    <?php
                } else {
                    ?>
                  <li><a class="dropdown-item" href="/login">Login</a></li>
                  <li><a class="dropdown-item" href="/register">Register</a></li>
                <?php } ?>
              </ul>
            </li class="nav-item">
          </ul>
        </div>
      </div>
    </nav>
        <?php

    }//end echoNav()


}//end class
