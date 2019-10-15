FROM ubuntu:bionic

# Install dependencies
RUN apt-get update && \
    apt-get install -y build-essential git libpcre3-dev golang

# Clone C-SDK repo
RUN git clone https://github.com/newrelic/c-sdk.git
RUN mkdir example

# Copy app files
COPY ex_container.c newrelic_common.c newrelic_common.h Makefile /example/

# Build and run
CMD cd /c-sdk/ && make && \
    cd ../example/ && make && \
    ./ex_container.out
