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

# Build daemon
WORKDIR /c-sdk
RUN make daemon

# Run daemon
CMD ./newrelic-daemon --logfile stdout --loglevel debug --address=daemon:31339  --watchdog-foreground
