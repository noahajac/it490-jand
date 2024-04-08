/*
Run and import the following for time functions to work correctly:
mysql_tzinfo_to_sql /usr/share/zoneinfo
*/

CREATE DATABASE jand_deploy;
USE jand_deploy;

CREATE USER 'jand'@'localhost' IDENTIFIED WITH auth_socket;
GRANT SELECT, INSERT, UPDATE, DELETE ON jand_deploy.* TO 'jand'@'localhost';

SET @@sql_mode=(SELECT REPLACE(@@sql_mode,'ONLY_FULL_GROUP_BY',''));

CREATE TABLE bundles (
    bundle_name VARCHAR(20) NOT NULL,
    version_number INT NOT NULL,
    status INT NOT NULL,
    PRIMARY KEY (bundle_name, version_number)
);
