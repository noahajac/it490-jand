<?php
/**
 * Contains main DB connector logic.
 *
 * @package JAND\DbConnector\Includes\Connector
 */

namespace JAND\DbConnector\Includes;

/**
 * Listens to requests from Rabbit and makes the appropriate
 * DB queries to craft a response. Will send DMZ requests if needed.
 */
class Connector
{

    /**
     * RabbitMqServer instance.
     *
     * @var \JAND\Common\RabbitMq\RabbitMqServer $server RabbitMQ server.
     */
    private static \JAND\Common\RabbitMq\RabbitMqServer $server;

    /**
     * Database PDO instance.
     *
     * @var \PDO $pdo PDO instance.
     */
    private static \PDO $pdo;


    /**
     * Requests from the message broker get processed here.
     *
     * @param mixed $request The request.
     *
     * @return mixed Request response, false if unknown.
     */
    private static function requestProcessor(mixed $request)
    {
        LogSender::sendLog('Received DB request of type: '.get_class($request));
        if ($request instanceof \JAND\Common\Messages\Frontend\LoginRequest) {
            return Responders\LoginResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\RegisterRequest) {
            return Responders\RegisterResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\SessionValidateRequest) {
            return Responders\SessionValidateResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\SessionInvalidateRequest) {
            return Responders\SessionInvalidateResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Shared\AirportCitySearchRequest) {
            return Responders\AirportCitySearchResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\GetUserTripsRequest) {
            return Responders\GetUserTripsResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\DeleteUserTripRequest) {
            return Responders\DeleteUserTripResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\CreateUserTripRequest) {
            return Responders\CreateUserTripResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Shared\FlightItinerarySearchRequest) {
            return Responders\FlightItinerarySearchResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Shared\HotelItinerarySearchRequest) {
            return Responders\HotelItinerarySearchResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Shared\PoiSearchRequest) {
            return Responders\PoiSearchResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\GetPoiKeywordsRequest) {
            return Responders\GetPoiKeywordsResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\GetUserKeywordPrefRequest) {
            return Responders\GetUserKeywordPrefResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\SetUserKeywordPrefRequest) {
            return Responders\SetUserKeywordPrefResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\DeleteReviewRequest) {
            return Responders\DeleteReviewResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\GetAirlineReviewsRequest) {
            return Responders\GetAirlineReviewsResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\GetHotelReviewsRequest) {
            return Responders\GetHotelReviewsResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\GetPoiReviewsRequest) {
            return Responders\GetPoiReviewsResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\CreateReviewRequest) {
            return Responders\CreateReviewResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\GetRecommendationsRequest) {
            return Responders\GetRecommendationsResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Shared\CreateBookingRequest) {
            return Responders\CreateBookingResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\GetBookingsRequest) {
            return Responders\GetBookingsResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\Frontend\HideRecommendationRequest) {
            return Responders\HideRecommendationResponder::respondToRequest($request, static::$pdo);
        } else if ($request instanceof \JAND\Common\Messages\DbTimer\RunEventsRequest) {
            return Responders\RunEventsResponder::respondToRequest($request, static::$pdo);
        } else {
            return false;
        }//end if

    }//end requestProcessor()


    /**
     * Creates RabbitMqServer and PDO, then starts listening to requests.
     *
     * @return void
     */
    public static function start()
    {
        static::$server = new \JAND\Common\RabbitMq\RabbitMqServer(
            __DIR__.'/../rabbitmq.ini',
            'db-frontend_db.server'
        );

        $dsn         = 'mysql:unix_socket=/var/run/mysqld/mysqld.sock;dbname=jand;charset=utf8';
        static::$pdo = new \PDO($dsn, 'jand');
        static::$pdo->setAttribute(\PDO::ATTR_ERRMODE, \PDO::ERRMODE_EXCEPTION);
        static::$pdo->setAttribute(\PDO::ATTR_EMULATE_PREPARES, true);
        static::$server->processRequests(
            function (string $requestString) {
                return serialize(
                    static::requestProcessor(unserialize($requestString))
                );
            },
            '/tmp/jand-db-connector-inhibit'
        );

    }//end start()


}//end class
