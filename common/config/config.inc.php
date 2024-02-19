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
  }

  /**
   * Get config instance.
   * @return Program config.
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
}
