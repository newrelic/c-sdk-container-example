# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.1.1] - 2019-11-27
### Daemon docker hub image
- The `docker-compose.yml` file now uses the [New Relic daemon docker hub image](https://hub.docker.com/r/newrelic/c-daemon). This greatly simplifies the daemon container setup. The daemon `Dockerfile` still exists, but is only used as reference until the `docker-compose.yml` is edited to use it. 
- The README was updated to include directions on how to use the daemon image or create your own daemon container. 

## [0.0.1] - 2019-10-24
### Initial public release
- New Relic C-SDK container example.