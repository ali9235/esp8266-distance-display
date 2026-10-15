#include "config.h"
#include "distance.h"
#if ENABLE_TFT
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
Adafruit_ST7735 screen(TFT_CS, TFT_DC, TFT_RST);
#endif
ranging::Filter distances;
uint32_t lastSample = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("NEW REFERENCE distance firmware; no measured accuracy claimed."));
#if ENABLE_RANGE_INPUT
  digitalWrite(TRIGGER_PIN, LOW); pinMode(TRIGGER_PIN, OUTPUT); pinMode(ECHO_PIN, INPUT);
#else
  Serial.println(F("No sensor GPIO enabled. Serial keys: n=simulated near, l=simulated far, f=timeout."));
#endif
#if ENABLE_TFT
  screen.initR(INITR_BLACKTAB); screen.setRotation(0); screen.fillScreen(ST77XX_BLACK);
#endif
}

void loop() {
  uint32_t now = millis();
#if !ENABLE_RANGE_INPUT
  uint8_t commands = 0;
  while (Serial.available() && commands++ < 16) {
    char c = char(Serial.read());
    if (c == 'n') distances.push(now, 1166); // Explicit simulated pulse, about 20 cm.
    if (c == 'l') distances.push(now, 5831); // Explicit simulated pulse, about 100 cm.
    if (c == 'f') distances.push(now, 0);
  }
#endif
  if (uint32_t(now - lastSample) >= 200UL) {
    lastSample = now;
#if ENABLE_RANGE_INPUT
    digitalWrite(TRIGGER_PIN, LOW); delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH); delayMicroseconds(10); digitalWrite(TRIGGER_PIN, LOW);
    distances.push(now, pulseIn(ECHO_PIN, HIGH, 30000UL));
#endif
    ranging::Reading value = distances.read(millis());
    Serial.print(ENABLE_RANGE_INPUT ? F("SENSOR ") : F("SIMULATION "));
    if (value.valid) { Serial.print(value.cm, 1); Serial.print(F(" cm near=")); Serial.println(value.near); }
    else Serial.println(F("NO VALID READING"));
#if ENABLE_TFT
    screen.fillScreen(ST77XX_BLACK); screen.setCursor(2, 10); screen.setTextSize(1);
    screen.setTextColor(ST77XX_WHITE); screen.println(ENABLE_RANGE_INPUT ? "SENSOR" : "SIMULATION");
    screen.setTextSize(2); screen.setTextColor(value.near ? ST77XX_RED : ST77XX_GREEN);
    if (value.valid) { screen.print(value.cm, 1); screen.println(" cm"); }
    else screen.println("NO ECHO");
#endif
  }
  delay(1);
}
