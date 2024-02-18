<?php

namespace JAND\Common\Autoload;

abstract class Autoload
{
  private static function findFile(string $path, int $iteration)
  {
    if (file_exists(__DIR__ . $path)) {
      return __DIR__ . $path;
    } else if ($iteration > 9) {
      return false;
    } else {
      return static::findFile('/..' . $path, ++$iteration);
    }
  }

  private static function autoload(string $name)
  {
    if (substr_compare($name, 'JAND\Common', 0, 11) === 0) {
      $path = substr($name, 4);
    } else {
      $path = preg_replace('/JAND\\\.*?\\\/', '', $name);
    }
    $path = str_replace('\\', '/', $path);
    $path = strtolower(preg_replace('/((?<!^)(?<!\/))[A-Z]/', '-$0', $path));
    $path .= '.inc.php';

    $file = static::findFile($path, 0);

    if ($file) {
      return require($file);
    } else {
      return false;
    }
  }


  static function register()
  {
    spl_autoload_register([__CLASS__, 'autoload']);
  }
}
