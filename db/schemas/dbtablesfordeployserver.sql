CREATE DATABASE IF NOT EXISTS deploymentserverdb;

USE deploymentserverdb;

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