/*
Run and import the following for time functions to work correctly:
mysql_tzinfo_to_sql /usr/share/zoneinfo
*/

CREATE DATABASE jand;
USE jand;

CREATE USER 'jand'@'localhost' IDENTIFIED WITH auth_socket;
GRANT SELECT, INSERT, UPDATE, DELETE ON jand.* TO 'jand'@'localhost';

SET GLOBAL event_scheduler = ON; 

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
   `longitute`    DECIMAL(8,5) NOT NULL,
   `state_code`   VARCHAR(5) NOT NULL,
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
    `pulled_on`    TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (origin, destination, start_date, end_date, adults, children, infants, one_way)
);

CREATE TABLE `hotel_bookings` (
    `booking_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `user_id` INT NOT NULL,
    `hotel_name` VARCHAR(255) NOT NULL,
    `check_in_date` DATE NOT NULL,
    `check_out_date` DATE NOT NULL,
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);

CREATE TABLE `flight_bookings` (
    `booking_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `user_id` INT NOT NULL,
    `flight_number` VARCHAR(50) NOT NULL,
    `departure_date` DATE NOT NULL,
    `arrival_date` DATE NOT NULL,
    `departure_location` VARCHAR(255) NOT NULL,
    `arrival_location` VARCHAR(255) NOT NULL,
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);

CREATE TABLE `hotel_reviews` (
    `review_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `user_id` INT NOT NULL,
    `hotel_name` VARCHAR(255) NOT NULL,
    `rating` DECIMAL(3,1) NOT NULL,
    `comment` TEXT,
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);

CREATE TABLE `airline_reviews` (
    `review_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `user_id` INT NOT NULL,
    `airline_name` VARCHAR(255) NOT NULL,
    `rating` DECIMAL(3,1) NOT NULL,
    `comment` TEXT,
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);

CREATE TABLE `user_vacation_preferences` (
    `user_id` INT NOT NULL,
    `romantic` BOOLEAN NOT NULL DEFAULT FALSE,
    `outdoors` BOOLEAN NOT NULL DEFAULT FALSE,
    `relax` BOOLEAN NOT NULL DEFAULT FALSE,
    `beach` BOOLEAN NOT NULL DEFAULT FALSE,
    `city` BOOLEAN NOT NULL DEFAULT FALSE,
    `fun_attractions` BOOLEAN NOT NULL DEFAULT FALSE,
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (`user_id`),
    FOREIGN KEY (`user_id`) REFERENCES `users`(`user_id`)
);

CREATE TABLE `hotel_cache` (
    `hotel_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `hotel_name` VARCHAR(255) NOT NULL,
    `check_in_date` DATE NOT NULL,
    `check_out_date` DATE NOT NULL,
    `price_per_night` DECIMAL(10, 2) NOT NULL,
    `last_updated` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

CREATE TABLE `poi_cache` (
    `poi_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `poi_name` VARCHAR(255) NOT NULL,
    `location` VARCHAR(255) NOT NULL,
    `rating` DECIMAL(3, 1),
    `last_updated` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

CREATE TABLE `poi_reviews` (
    `review_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `poi_id` INT NOT NULL,
    `user_id` INT NOT NULL,
    `rating` DECIMAL(3, 1) NOT NULL,
    `comment` TEXT,
    `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (`poi_id`) REFERENCES `poi_cache`(`poi_id`),
    FOREIGN KEY (`user_id`) REFERENCES `users`(`user_id`)
);
