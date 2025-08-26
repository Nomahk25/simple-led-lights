// ESP32 Traffic Light - Wokwi + Real Hardware
// Author: Nomanguni
// Repository: (https://github.com/Nomahk25)
//
// Pins used (ESP32 DevKit V1):
//   RED_LED    -> GPIO 18
//   YELLOW_LED -> GPIO 19
//   GREEN_LED  -> GPIO 21
//
// Timing defaults mimic a simple traffic light cycle.
// You can tweak the *_MS values to change durations.
//
#define RED_LED     18
#define YELLOW_LED  19
#define GREEN_LED   21

const uint16_t GREEN_MS  = 5000;   // 5s
const uint16_t YELLOW_MS = 2000;   // 2s
const uint16_t RED_MS    = 5000;   // 5s

const uint16_t GREEN_BLINK_MS = 300; // blink speed for green
const uint8_t  GREEN_BLINKS   = 3;   // number of green blinks

void setLights(bool red, bool yellow, bool green) {
  digitalWrite(RED_LED, red   ? HIGH : LOW);
  digitalWrite(YELLOW_LED, yellow ? HIGH : LOW);
  digitalWrite(GREEN_LED, green ? HIGH : LOW);
}

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // Start with all OFF for a moment
  setLights(false, false, false);
  delay(500);
}

void loop() {
  // 1) Green - go
  setLights(false, false, true);
  delay(GREEN_MS);

  // Optional blinking green before yellow
  for (uint8_t i = 0; i < GREEN_BLINKS; i++) {
    setLights(false, false, false);
    delay(GREEN_BLINK_MS);
    setLights(false, false, true);
    delay(GREEN_BLINK_MS);
  }

  // 2) Yellow - prepare to stop
  setLights(false, true, false);
  delay(YELLOW_MS);

  // 3) Red - stop
  setLights(true, false, false);
  delay(RED_MS);

  // Loop back to green
}
