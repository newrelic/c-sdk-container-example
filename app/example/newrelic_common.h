/*
 * Copyright[2019] New Relic Corporation.All rights reserved.
 * SPDX - License - Identifier : Apache - 2.0
 */

/*!
 * @file newrelic_common.h
 *
 * @brief Common constants and function declarations for New Relic C SDK
 * example code.
 */
#ifndef LIBNEWRELIC_COMMON_H
#define LIBNEWRELIC_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libnewrelic.h"

#define ENV_NOTICE                                                              \
  ("This example program depends on environment variables NEW_RELIC_APP_NAME, " \
   "NEW_RELIC_DAEMON_ADDRESS, and NEW_RELIC_LICENSE_KEY.")

  /* Common function declarations */
  bool customize_config(newrelic_app_config_t **config_ptr);
  bool example_init(char *daemon_address);
  char* get_app_name(void);
  char* get_daemon_address(void);
  char* get_license_key(void);

#ifdef __cplusplus
}
#endif

#endif
