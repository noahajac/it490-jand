<?php
/**
 * Contains a helper function for dates in forms.
 *
 * @package JAND\Frontend\Includes\DateCallback
 */

namespace JAND\Frontend\Includes;

/**
 * Date callback helper.
 */
abstract class DateCallback
{


    /**
     * Checks if submitted date string is valid.
     *
     * @param string $date Date string.
     *
     * @return false|\DateTime False if not, DateTime if it is.
     */
    public static function checkDate(string $date)
    {
        if (empty($date)) {
            return false;
        } else {
            try {
                return new \DateTime($date);
            } catch (\DateMalformedStringException $e) {
                return false;
            }
        }

    }//end checkDate()


}//end class
