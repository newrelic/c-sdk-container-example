#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
 * A standalone example that demonstrates to users how to
 * configure logging, configure an app, connect an app,
 * start a transaction and a segment, and cleanly destroy
 * everything using a daemon on a different host.
 */
#include "libnewrelic.h"
#include "newrelic_common.h"

int main(void) {
  newrelic_app_t* app = 0;
  newrelic_txn_t* txn = 0;
  newrelic_app_config_t* config = 0;
  newrelic_external_segment_params_t params = {
      .procedure = "GET",
      .uri = "https://httpbin.org/delay/1",
  };
  newrelic_segment_t* seg = 0;

  /* Get the New Relic application name from environment, NEW_RELIC_APP_NAME */
  char* app_name = get_app_name();
  if (NULL == app_name) {
    return -1;
  }

  /* Get the New Relic daemon address from environment, 
   * NEW_RELIC_DAEMON_ADDRESS */
  char* daemon_address = get_daemon_address();
  if (NULL == daemon_address) {
    return -1;
  }

  /* Get the New Relic license key from environment, NEW_RELIC_LICENSE_KEY */
  char* license_key = get_license_key();
  if (NULL == license_key) {
    return -1;
  }

  /* Point to the daemon by using a valid daemon address */
  if (false == example_init(daemon_address)) {
    return -1;
  }

  config = newrelic_create_app_config(app_name, license_key);
  customize_config(&config);

  /* Change the transaction tracer threshold to ensure a trace is generated */
  config->transaction_tracer.threshold = NEWRELIC_THRESHOLD_IS_OVER_DURATION;
  config->transaction_tracer.duration_us = 1;

  /* Wait up to 15 seconds for the SDK to connect to the daemon */
  app = newrelic_create_app(config, 15000);
  newrelic_destroy_app_config(&config);

  /* Start a web transaction and a segment */
  txn = newrelic_start_web_transaction(app, "ExampleContainerWebTransaction");

  /* Fake a web request by sleeping for one second. In a more typical
   * instrumentation scenario the start() and stop() calls for the external
   * segment would be before and after code performing an HTTP or SOAP
   * operation, for example. */
  seg = newrelic_start_external_segment(txn, &params);
  sleep(1);

  /* End the segment and web transaction */
  newrelic_end_segment(txn, &seg);
  newrelic_end_transaction(&txn);

  newrelic_destroy_app(&app);

  return 0;
}
