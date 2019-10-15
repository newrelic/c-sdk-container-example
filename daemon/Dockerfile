FROM ubuntu:bionic

# Install dependencies
RUN apt-get update && \
  apt-get install -y build-essential git libpcre3-dev golang

# Clone C-SDK repo
RUN git clone https://github.com/newrelic/c-sdk.git

# Build and run
CMD cd c-sdk && make daemon && \
  ./newrelic-daemon --logfile stdout --loglevel debug --address=daemon:31339  --watchdog-foreground
