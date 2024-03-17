<?php
/**
 * Represents an IATA code such as an airport, city, or airline.
 *
 * @package JAND\Common\Trips\IATACode
 */

namespace JAND\Common\Trips;

/**
 * An IATA code such as airport, city, or airline.
 */
abstract class IATACode
{

    /**
     * IATA code.
     *
     * @var string $code IATA code.
     */
    private string $code;

    /**
     * Location name.
     * May be null if coming from DMZ.
     *
     * @var string $name Location name.
     */
    private ?string $name;


    /**
     * Create an IATA code object.
     *
     * @param string $code IATA code.
     * @param string $name Name of location/thing.
     */
    public function __construct(string $code, ?string $name)
    {
        $this->code = $code;
        $this->name = $name;

    }//end __construct()


    /**
     * Gets IATA code.
     *
     * @return string IATA code.
     */
    public function getCode()
    {
        return $this->code;

    }//end getCode()


    /**
     * Gets name.
     *
     * @return ?string Name represented by code.
     */
    public function getName()
    {
        return $this->name;

    }//end getName()


}//end class
