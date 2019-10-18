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
  