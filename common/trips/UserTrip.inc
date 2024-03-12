<?php
/**
 * A user's trip.
 *
 * @package JAND\Common\Trips\UserTrip
 */

namespace JAND\Common\Trips;

/**
 * A user's trip.
 */
class Trip
{

    /**
     * Trip's name.
     *
     * @var string $tripName Trip name.
     */
    private string $tripName;

    /**
     * List of flights.
     *
     * @var Flight[] $flights List of flights.
     */
    private array $flights;

    /**
     * List of hotels.
     *
     * @var Hotel[] $hotels List of hotels.
     */
    private array $hotels;

    /**
     * List of POIs.
     *
     * @var Poi[] $hotels List of POIs.
     */
    private array $pois;

    /**
     * Trip start date.
     *
     * @var \DateTime $startDate Trip start date.
     */
    private \DateTime $startDate;

    /**
     * Trip end date.
     *
     * @var \DateTime $endDate Trip end date.
     */
    private \DateTime $endDate;
}//end class
