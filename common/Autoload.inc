<?php
/**
 * Contains logic that autoloads files based on class names.
 *
 * @package JAND\Common\Autoload
 */

namespace JAND\Common;

/**
 * Autoload files based on class name.
 */
abstract class Autoload
{


    /**
     * Recursively goes up a path until a file is found.
     * Up to 10 times.
     *
     * @param string  $path      Relative path to find file for, with leading "/".
     * @param integer $iteration Current iteration, will stop once above 9.
     *
     * @return false|string String of file, false if not found.
     */
    private static function findFile(string $path, int $iteration)
    {
        if (php_sapi_name() === 'cli') {
            $currentDir = dirname($_SERVER['PHP_SELF']);
        } else {
            $currentDir = $_SERVER['DOCUMENT_ROOT'];
        }

        if (file_exists($currentDir.$path)) {
            return $currentDir.$path;
        } else if ($iteration > 9) {
            return false;
        } else {
            return static::findFile('/..'.$path, ++$iteration);
        }

    }//end findFile()


    /**
     * Requires files based on class name.
     *
     * @param string $name Name of class, including namespace.
     *
     * @return boolean If successful.
     */
    private static function autoloadClass(string $name)
    {
        if (substr_compare($name, 'JAND\Common', 0, 11) === 0) {
            $path = substr($name, 4);
        } else {
            $path = preg_replace('/JAND\\\.*?\\\/', '\\', $name);
        }

        $path       = str_replace('\\', '/', $path);
        $pathEnd    = strrpos($path, '/');
        $className  = substr($path, $pathEnd);
        $path       = substr($path, 0, $pathEnd);
        $path       = strtolower(preg_replace('/((?<!^)(?<!\/))[A-Z]/', '-$0', $path));
        $className .= '.inc';

        $file = static::findFile($path.$className, 0);

        if ($file) {
            include $file;
            return true;
        } else {
            return false;
        }

    }//end autoloadClass()


    /**
     * Register autoload function in PHP.
     *
     * @return void
     */
    public static function register()
    {
        spl_autoload_register([__CLASS__, 'autoloadClass']);

    }//end register()


}//end class
