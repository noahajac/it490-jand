/*
Run and import the following for time functions to work correctly:
mysql_tzinfo_to_sql /usr/share/zoneinfo
*/

CREATE DATABASE jand;
USE jand;

CREATE USER 'jand'@'localhost' IDENTIFIED WITH auth_socket;
GRANT SELECT, INSERT, UPDATE, DELETE ON jand.* TO 'jand'@'localhost';

SET @@sql_mode=(SELECT REPLACE(@@sql_mode,'ONLY_FULL_GROUP_BY',''));

CREATE TABLE users (
    `user_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `password` VARCHAR(255) NOT NULL,
    `email` VARCHAR(255) NOT NULL,
    `first_name` VARCHAR(255) NOT NULL,
    `last_name` VARCHAR(255) NOT NULL,
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE sessions (
    `session_token` VARCHAR(255) NOT NULL PRIMARY KEY,
    `user_id` INT NOT NULL,
    `expires_at` TIMESTAMP NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);

CREATE TABLE airport_cities (
   `iata_code`    CHAR(3) NOT NULL PRIMARY KEY,
   `name`         VARCHAR(255) NOT NULL,
   `latitude`     DECIMAL(7,5) NOT NULL,
   `longitude`    DECIMAL(8,5) NOT NULL,
   `country_code` CHAR(2) NOT NULL,
   `created_at`   TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

CREATE TABLE `user_trips` (
    `trip_id`    INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `user_id`    INT NOT NULL,
    `iata_code`  CHAR(3) NOT NULL,
    `start_date` DATE NOT NULL,
    `end_date`   DATE NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users(user_id),
    FOREIGN KEY (iata_code) REFERENCES airport_cities(iata_code)
);

CREATE TABLE `airlines` (
    `iata_code` CHAR(2) NOT NULL PRIMARY KEY,
    `name`      VARCHAR(255) NOT NULL
);

CREATE TABLE `flights` (
    `flight_id`       INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `depart_airport`  CHAR(3) NOT NULL,
    `arrival_airport` CHAR(3) NOT NULL,
    `depart_time`     DATETIME NOT NULL,
    `arrival_time`    DATETIME NOT NULL,
    `airline`         CHAR(2) NOT NULL,
    `flight_no`       INT NOT NULL,
    `class_name`      VARCHAR(255) NOT NULL,
    `created_at`      TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (depart_airport) REFERENCES airport_cities(iata_code),
    FOREIGN KEY (arrival_airport) REFERENCES airport_cities(iata_code),
    FOREIGN KEY (airline) REFERENCES airlines(iata_code),
    UNIQUE (depart_airport, arrival_airport, depart_time, arrival_time, airline, flight_no, class_name)
);

CREATE TABLE `flight_itineraries` (
    `itinerary_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `origin`       CHAR(3) NOT NULL,
    `destination`  CHAR(3) NOT NULL,
    `start_date`   DATE NOT NULL,
    `end_date`     DATE NOT NULL,
    `total_price`  DECIMAL(10,2) NOT NULL,
    `adults`       INT NOT NULL,
    `children`     INT NOT NULL DEFAULT 0,
    `infants`      INT NOT NULL DEFAULT 0,
    `one_way`      BOOLEAN NOT NULL DEFAULT 0,
    `created_at`   TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (origin) REFERENCES airport_cities(iata_code),
    FOREIGN KEY (destination) REFERENCES airport_cities(iata_code)
);

CREATE TABLE `itinerary_out_segments` (
    `itinerary_id` INT NOT NULL,
    `flight_id`    INT NOT NULL,
    `position`     INT NOT NULL,
    FOREIGN KEY (itinerary_id) REFERENCES flight_itineraries(itinerary_id),
    FOREIGN KEY (flight_id) REFERENCES flights(flight_id),
    PRIMARY KEY (itinerary_id, flight_id),
    UNIQUE (itinerary_id, position)
);

CREATE TABLE `itinerary_return_segments` (
    `itinerary_id` INT NOT NULL,
    `flight_id`    INT NOT NULL,
    `position`     INT NOT NULL,
    FOREIGN KEY (itinerary_id) REFERENCES flight_itineraries(itinerary_id),
    FOREIGN KEY (flight_id) REFERENCES flights(flight_id),
    PRIMARY KEY (itinerary_id, flight_id),
    UNIQUE (itinerary_id, position)
);

CREATE TABLE `flight_queries` (
    `origin`       CHAR(3) NOT NULL,
    `destination`  CHAR(3) NOT NULL,
    `start_date`   DATE NOT NULL,
    `end_date`     DATE NOT NULL,
    `adults`       INT NOT NULL,
    `children`     INT NOT NULL DEFAULT 0,
    `infants`      INT NOT NULL DEFAULT 0,
    `one_way`      BOOLEAN NOT NULL DEFAULT 0,
    `pulled_on`    TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    PRIMARY KEY (origin, destination, start_date, end_date, adults, children, infants, one_way),
    FOREIGN KEY (origin) REFERENCES airport_cities(iata_code),
    FOREIGN KEY (destination) REFERENCES airport_cities(iata_code)
);

CREATE TABLE `hotels` (
    `hotel_id`   INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `hotel_code` CHAR(8) NOT NULL,
    `hotel_name` VARCHAR(255) NOT NULL,
    `city`       CHAR(3) NOT NULL,
    `pulled_on`  TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (city) REFERENCES airport_cities(iata_code)
);

CREATE TABLE `hotel_itineraries` (
    `itinerary_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `hotel_id`     INT NOT NULL,
    `check_in`     DATE NOT NULL,
    `check_out`    DATE NOT NULL,
    `adults`       INT NOT NULL,
    `total_price`  DECIMAL(10, 2) NOT NULL,
    `pulled_on`    TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (hotel_id) REFERENCES hotels(hotel_id)
);

CREATE TABLE `hotel_queries` (
    `city`      CHAR(3) NOT NULL,
    `check_in`  DATE NOT NULL,
    `check_out` DATE NOT NULL,
    `adults`    INT NOT NULL,
    `pulled_on` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    PRIMARY KEY (city, check_in, check_out, adults),
    FOREIGN KEY (city) REFERENCES airport_cities(iata_code)
);

CREATE TABLE `poi` (
    `poi_id`    INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `poi_name`  VARCHAR(255) NOT NULL,
    `city`      CHAR(3) NOT NULL,
    `pulled_on` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    UNIQUE (poi_name, city),
    FOREIGN KEY (city) REFERENCES airport_cities(iata_code)
);

CREATE TABLE `hide_poi` (
    `poi_id` INT NOT NULL,
    `user_id` INT NOT NULL,
    PRIMARY KEY (poi_id, user_id),
    FOREIGN KEY (poi_id) REFERENCES poi(poi_id),
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);

CREATE TABLE `poi_keywords` (
    `poi_id`    INT NOT NULL,
    `keyword`   VARCHAR(30) NOT NULL,
    PRIMARY KEY (poi_id, keyword),
    FOREIGN KEY (poi_id) REFERENCES poi(poi_id)
);

CREATE TABLE `poi_queries` (
    `city`      CHAR(3) NOT NULL PRIMARY KEY,
    `pulled_on` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (city) REFERENCES airport_cities(iata_code)
);

CREATE TABLE `user_keyword_preferences` (
    `user_id` INT NOT NULL,
    `keyword` VARCHAR(30) NOT NULL,
    PRIMARY KEY (user_id, keyword),
    FOREIGN KEY (`user_id`) REFERENCES `users`(`user_id`)
);

CREATE TABLE `airline_reviews` (
    `review_id`  INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `user_id`    INT NOT NULL,
    `iata_code`  CHAR(3) NOT NULL,
    `rating`     INT NOT NULL,
    `comment`    TEXT,
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    UNIQUE (user_id, iata_code),
    FOREIGN KEY (user_id) REFERENCES users(user_id),
    FOREIGN KEY (iata_code) REFERENCES airlines(iata_code)
);

CREATE TABLE `hotel_reviews` (
    `review_id`  INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `user_id`    INT NOT NULL,
    `hotel_id`   INT NOT NULL,
    `rating`     INT NOT NULL,
    `comment`    TEXT,
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    UNIQUE (user_id, hotel_id),
    FOREIGN KEY (user_id) REFERENCES users(user_id),
    FOREIGN KEY (hotel_id) REFERENCES hotels(hotel_id)
);

CREATE TABLE `poi_reviews` (
    `review_id`  INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `user_id`    INT NOT NULL,
    `poi_id`     INT NOT NULL,
    `rating`     INT NOT NULL,
    `comment`    TEXT,
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    UNIQUE (user_id, poi_id),
    FOREIGN KEY (user_id) REFERENCES users(user_id),
    FOREIGN KEY (poi_id) REFERENCES poi(poi_id)
);

CREATE TABLE `hotel_bookings` (
    `user_id` INT NOT NULL,
    `itinerary_id` INT NOT NULL,
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    `notified` BOOLEAN NOT NULL DEFAULT 0,
    PRIMARY KEY (user_id, itinerary_id),
    FOREIGN KEY (user_id) REFERENCES users(user_id),
    FOREIGN KEY (itinerary_id) REFERENCES hotel_itineraries(itinerary_id)
);

CREATE TABLE `flight_bookings` (
    `user_id` INT NOT NULL,
    `itinerary_id` INT NOT NULL,
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    `notified` BOOLEAN NOT NULL DEFAULT 0,
    PRIMARY KEY (user_id, itinerary_id),
    FOREIGN KEY (user_id) REFERENCES users(user_id),
    FOREIGN KEY (itinerary_id) REFERENCES flight_itineraries(itinerary_id)
);
