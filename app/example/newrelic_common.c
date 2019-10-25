/*
 * Copyright[2019] New Relic Corporation.All rights reserved.
 * SPDX - License - Identifier : Apache - 2.0
 */

/*!
 * newrelic_common.c
 *
 * @brief Common function implementations for New Relic C SDK container example code.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "newrelic_common.h"

/*
 * @brief Customize a configuration
 *
 * @param [in] config_ptr The address of an agent configuration created using
 * newrelic_create_app_config().
 *
 * @return false if config_ptr or *config_ptr are NULL; true otherwise.
 */
bool customize_config(newrelic_app_config_t** config_ptr) {
  if (NULL != config_ptr && NULL != *config_ptr) {
    char* collector = getenv("NEW_RELIC_HOST");
    newrelic_app_config_t* config = *config_ptr;

    if (NULL != collector) {
      strcpy(config->redirect_collector, collector);
    } else {
      printf("Using default SDK configuration for collector...\n");
    }

    return true;
  }
  return false;
}

/*!
 * @brief Configure the log and initialize daemon connection.
 *
 * @return true if log and daemon connection are configred. False otherwise
 */
bool example_init(char* daemon_address) {
  if (!newrelic_configure_log("./c_sdk.log", NEWRELIC_LOG_INFO)) {
    printf("Error configuring logging.\n");
    return false;
  }

  if (!newrelic_init(daemon_address, 0)) {
    printf("Error connecting to daemon.\n");
    return false;
  }

  return true;
}

/*!
 * @brief Get the New Relic application name from environment,
 * NEW_RELIC_APP_NAME.
 *
 * @return A pointer to the environment variable NEW_RELIC_APP_NAME; NULL if it
 * is not defined.
 */
char* get_app_name(void) {
  char* app_name = getenv("NEW_RELIC_APP_NAME");

  if (NULL == app_name) {
    printf(ENV_NOTICE);
    printf(
        "\nEnvironment variable NEW_RELIC_APP_NAME must be set to a meaningful "
        "application name.\n");
  }

  return app_name;
}

/*!
 * @brief Get the New Relic Daemon Address from environment,
 * NEW_RELIC_DAEMON_ADDRESS.
 *
 * @return A pointer to the environment variable NEW_RELIC_DAEMON_ADDRESS; NULL
 * if it is not defined.
 */
char* get_daemon_address(void) {
  char* daemon_address = getenv("NEW_RELIC_DAEMON_ADDRESS");
  if (NULL == daemon_address) {
    printf(ENV_NOTICE);
    printf(
        "Environment variable NEW_RELIC_DAEMON_ADDRESS must be set to a "
        "valid address in the format (HOST:PORT).\n");
  }

  return daemon_address;
}

/*!
 * @brief Get the New Relic license key from environment, NEW_RELIC_LICENSE_KEY.
 *
 * @return A pointer to the environment variable NEW_RELIC_LICENSE_KEY; NULL if
 * it is not defined.
 */
char* get_license_key(void) {
  char* license_key = getenv("NEW_RELIC_LICENSE_KEY");

  if (NULL == license_key) {
    printf(ENV_NOTICE);
    printf(
        "\nEnvironment variable NEW_RELIC_LICENSE_KEY must be set to a valid "
        "New Relic license key.\n");
  }

  return license_key;
}
