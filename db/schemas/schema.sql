/*
Run and import the following for time functions to work correctly:
mysql_tzinfo_to_sql /usr/share/zoneinfo
*/

CREATE DATABASE jand;
USE jand;

CREATE USER 'jand'@'localhost' IDENTIFIED WITH auth_socket;
GRANT SELECT, INSERT, UPDATE, DELETE ON jand.* TO 'jand'@'localhost';

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

CREATE TABLE `user_trips` (
    `trip_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `user_id` INT NOT NULL,
    `destination` VARCHAR(255) NOT NULL,
    `start_date` DATE NOT NULL,
    `end_date` DATE NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users(user_id)
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

CREATE TABLE `flight_cache` (
    `flight_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    `flight_number` VARCHAR(50) NOT NULL,
    `departure_date` DATE NOT NULL,
    `arrival_date` DATE NOT NULL,
    `departure_location` VARCHAR(255) NOT NULL,
    `arrival_location` VARCHAR(255) NOT NULL,
    `price` DECIMAL(10, 2) NOT NULL,
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
