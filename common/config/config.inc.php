<?php

/**
 * Contains logic that parses config file.
 */

namespace JAND\Common\Config;

/**
 * Program config information.
 */
class Config
{
  /** Singleton instance of {@link \JAND\Common\Config\Config} class. */
  private static Config $instance;

  /** Whether dev mode is enabled. */
  private bool $devMode;

  /** Name of session cookie. */
  private string $sessionCookieName;

  /**
   * Create instance of Config class.
   * Read config.ini into class properties.
   * */
  private function __construct()
  {
    $ini = parse_ini_file('config.ini', true);

    if (!($this->devMode = $ini['jand']['devMode'] ?? null)) {
      $this->devMode = false;
    }

    if (!($this->sessionCookieName = $ini['jand']['sessionCookieName'] ?? null)) {
      $this->sessionCookieName = 'SESSION';
    }
  }

  /**
   * Get config instance.
   * @return \JAND\Common\Config Program config.
   * */
  static function getConfig()
  {
    if (!isset(static::$instance)) {
      static::$instance = new Config();
    }

    return static::$instance;
  }

  /**
   * Get whether dev mode is enabled.
   * @return bool Whether dev mode is enabled.
   */
  function getDevMode()
  {
    return $this->devMode;
  }

  /**
   * Get session cookie name.
   * @return string Session cookie name.
   */
  function getSessionCookieName()
  {
    return $this->sessionCookieName;
  }
}
