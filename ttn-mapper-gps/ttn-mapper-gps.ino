/*******************************************************************************
 * ttn-mapper-gps
 *
 * Send TTN packets with GPS payload for tracking via ttnmapper.org
 *
 * This code runs on an Adafruit Feather M0 with LoRa with GPS FeatherWing,
 * status displayed on Adafruit OLED FeatherWing
 *
 *******************************************************************************/

#include <lmic.h>
#include "Serial_Display.h"
#include "gps.h"

// Display
Serial_Display display = Serial_Display();

// Init radio
extern osjob_t init_lora_job;
extern void init_lora (osjob_t* j);

// Update the display every seccond
const uint8_t update_display_interval = 1;
static osjob_t update_display_job;
static void update_display(osjob_t* j)
{
  // Update screen
  display.update();
  // Reschedule
  os_setTimedCallback(&update_display_job,
                      os_getTime() + sec2osticks(update_display_interval),
                      update_display);
}

void setup() {
  Serial.begin(115200);
  delay(1000); // Wait one second for Serial to catch up
  Serial.println();
  Serial.println("Welcome to Telokanda Weather Balloons");

  // initialize the scheduler
  os_init();

  // initialize GPS
  gps_init();
  delay(2000);

  // Schedule jobs
  // Display updates
  os_setCallback(&update_display_job, update_display);
  // Initialize radio
  os_setCallback(&init_lora_job, init_lora);
}

void loop() {
  // Run the scheduler
  os_runloop_once();
}
