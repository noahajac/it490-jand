<?php

/**
 * Contains logic that autoloads files based on class names.
 */

namespace JAND\Common\Autoload;

/**
 * Autoload files based on class name.
 */
abstract class Autoload
{

  /**
   * Recursively goes up a path until a file is found.
   * Up to 10 times.
   * @param string $path Relative path to find file for, with leading "/".
   * @param int $iteration Current iteration, will stop once above 9.
   * @return false|string String of file, false if not found.
   */
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

  /**
   * Requires files based on class name.
   * @param string $name Name of class, including namespace.
   */
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

  /**
   * Register autoload function in PHP.
   */
  static function register()
  {
    spl_autoload_register([__CLASS__, 'autoload']);
  }
}
