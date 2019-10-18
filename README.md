# C-SDK And Daemon Containers Example

**This is an unsupported example. This project is provided AS-IS WITHOUT
WARRANTY OR SUPPORT.**

The C SDK is a software development kit that allows users to manually instrument applications written in C or C++ for Linux 64-bit operating systems. With the release of [C-SDK version 1.2](https://github.com/newrelic/c-sdk/blob/master/CHANGELOG.md#120), the application and daemon no longer have to reside on the same host and can now communicate over an IPv4 or IPv6 TCP socket. This repository contains a simple application that demonstrates how an instrumented application and daemon can be set up on separate containers.

**Data transmitted from an instrumented application to the daemon is not encrypted. We recommend only using a private network connection between the app and daemon.**

## Example Application

The application uses the following environment variables.

|       Var Name       | Description | Required |
| -------------------- | ----------- | ------------- |
| NEW_RELIC_LICENSE_KEY | The New Relic License Key. | Required |
| NEW_RELIC_APP_NAME | The New Relic app name that will appear in the UI. | Required |
| NEW_RELIC_HOST | New Relic collector host. If NULL will be set to the default of collector.newrelic.com | Not required |

Run the application by using the `run_app` script:
* `./run_app`

### Instrumented Application Container Configuration
The app `Dockerfile` below shows how to configure an application container:
* All the required packages to build and run are installed. See [C-SDK Requirements](https://github.com/newrelic/c-sdk#requirements) for more information. 
* [C-SDK](https://github.com/newrelic/c-sdk) is cloned into the container.
* The files in the `app/example` directory are copied into the container `example` directory.
* The `C-SDK` and `example` are both built. 
* Dockerize is used to overcome possible synchronization issues. If the app container is ready first, it will wait for the daemon container to be available on the daemon address.
* Run using `./ex_container.out`.

Visit [C-SDK getting started](https://github.com/newrelic/c-sdk/blob/master/GUIDE.md#getting-started) for more details on `ex_container.c`.

`app/Dockerfile`:
```
FROM ubuntu:bionic

# Install dependencies
RUN apt-get update && apt-get install -y \
  build-essential \
  git \
  golang \
  libpcre3-dev \
  wget

# Clone C-SDK repo
RUN git clone https://github.com/newrelic/c-sdk.git
RUN mkdir example

# Copy app files
COPY ["/example/*", "/example/"]

# Build C-SDK and example app
WORKDIR /c-sdk
RUN make
WORKDIR /example/
RUN make 

# Use dockerize so the app container waits for the daemon container before connecting
ENV DOCKERIZE_VERSION v0.6.0
RUN wget https://github.com/jwilder/dockerize/releases/download/$DOCKERIZE_VERSION/dockerize-alpine-linux-amd64-$DOCKERIZE_VERSION.tar.gz \
  && tar -C /usr/local/bin -xzvf dockerize-alpine-linux-amd64-$DOCKERIZE_VERSION.tar.gz \
  && rm dockerize-alpine-linux-amd64-$DOCKERIZE_VERSION.tar.gz

# Run example app
CMD dockerize -wait tcp://${NEW_RELIC_DAEMON_ADDRESS} \
  && ./ex_container.out
```

### Daemon Container Configuration
The daemon `Dockerfile` below shows how to configure a daemon container:
* All the required packages to build and run are installed. See [C-SDK Requirements](https://github.com/newrelic/c-sdk#requirements) for more information. 
* [C-SDK](https://github.com/newrelic/c-sdk#requirements) is cloned into the container.
* The `daemon` is compiled and started.
* Run using the `--address` and `--watchdog-foreground` 
    - `--address` argument is used to set a port the daemon is accepting connections on. `--address` and `NEW_RELIC_DAEMON_ADDRESS` (environment variable in the app section of the `docker_compose.yml`) must match.
    - `--watchdog-foreground` argument ensures that the daemon runs in the foreground.
    - `--logfile` is set to `stdout` and `--loglevel` is set to `debug`. See [C-SDK daemon logs](https://github.com/newrelic/c-sdk/blob/master/GUIDE.md#daemon-logs) for more information.

`daemon/Dockerfile`:
```
FROM ubuntu:bionic

# Install dependencies
RUN apt-get update && apt-get install -y \
  git \
  golang

# Clone C-SDK repo
RUN git clone https://github.com/newrelic/c-sdk.git

# Build daemon
WORKDIR /c-sdk
RUN make daemon

# Run daemon
CMD ./newrelic-daemon --logfile stdout --loglevel debug --address=daemon:31339  --watchdog-foreground

```

### Application Docker Compose
The `docker_compose.yml` file below displays the container structure of the example application. Environment variables used in `app/Dockerfile` are set here (using a valid `NEW_RELIC_LICENSE_KEY`, `NEW_RELIC_APP_NAME` and `NEW_RELIC_HOST` ). The port the daemon is listening on `expose` is set here. This must match the `--address` (daemon startup argument) and `NEW_RELIC_DAEMON_ADDRESS` (in the app `environement` section).

```
version: '2.4'

services:
  app:
    build:
      context: app 
    depends_on:
      - "daemon"
    environment:
      NEW_RELIC_LICENSE_KEY: ${NEW_RELIC_LICENSE_KEY}
      NEW_RELIC_APP_NAME: ${NEW_RELIC_APP_NAME}
      NEW_RELIC_HOST: ${NEW_RELIC_HOST}
      NEW_RELIC_DAEMON_ADDRESS: "daemon:31339"
  daemon:
    build:
      context: daemon
    expose:
      - "31339"
```