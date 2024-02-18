<?php

namespace JAND\Common\Config;

class Config {
  private static Config $instance;
  private bool $devMode;
  
  private function __construct()
  {
    $ini = parse_ini_file('config.ini', true);
    
    if (!($this->devMode = $ini['jand']['devMode'] ?? null)) {
      $this->devMode = false;
    }
  }

  static function getConfig() {
    if (!isset(static::$instance)) {
      static::$instance = new Config();
    }

    return static::$instance;
  }

  function getDevMode() {
    return $this->devMode;
  }
}
