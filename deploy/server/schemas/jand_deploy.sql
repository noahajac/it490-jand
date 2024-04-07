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
    bundle_name VARCHAR(255),
    version_number INT,
    status VARCHAR(255),
    PRIMARY KEY (bundle_name, version_number)
);

CREATE TABLE bundles_links (
    bundle_a_name VARCHAR(255),
    bundle_a_version INT,
    bundle_b_name VARCHAR(255),
    bundle_b_version INT,
    FOREIGN KEY (bundle_a_name, bundle_a_version) REFERENCES bundles(bundle_name, version_number),
    FOREIGN KEY (bundle_b_name, bundle_b_version) REFERENCES bundles(bundle_name, version_number)
);
