#------------------------------------------------------------------------------
# Copyright [2019] New Relic Corporation. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#------------------------------------------------------------------------------

#
# Makefile for New Relic C SDK Code Examples
#

# This Makefile presumes that libnewrelic.h and libnewrelic.a are at the following
# locations:

LIBNEWRELIC_A_LOCATION = ../c-sdk
LIBNEWRELIC_H_LOCATION = ../c-sdk/include

# Pull in PCRE config.
PCRE_CFLAGS := $(shell pcre-config --cflags)
PCRE_LIBS := $(shell pcre-config --libs)

EXAMPLES := ex_container.out

all: $(EXAMPLES)

ex_%.out: ex_%.o newrelic_common.o ../c-sdk/libnewrelic.a
	$(CC) -o $@ $< newrelic_common.o -rdynamic -L$(LIBNEWRELIC_A_LOCATION) -lnewrelic $(PCRE_LIBS) -pthread -lm

%.o: %.c
	$(CC) -c $< -o $@ -I$(LIBNEWRELIC_H_LOCATION) $(PCRE_CFLAGS)

clean:
	rm -f *.o $(EXAMPLES) c_sdk.log
