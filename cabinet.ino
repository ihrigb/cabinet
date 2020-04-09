#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define DOOR_PIN 2
#define TOPLIGHT_PIN 3
#define STRIP_PIN 4
#define NUM_PIXELS 46

#define FADE_TIME 5000    // 5 seconds
#define TIMEOUT 120000   // 2 minutes

// Strip color
#define STRIP_RED 0
#define STRIP_GREEN 0
#define STRIP_BLUE 255

unsigned long start;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, STRIP_PIN, NEO_GRB + NEO_KHZ800);

void setupPins() {
  pinMode(DOOR_PIN, INPUT);
}

void reset() {
  allOff();
  start = 0;
}

void setup() {
  // Serial.begin(9600);
  setupPins();
  strip.begin();
  reset();
}

void loop() {
   if (!doorOpen()) {
    Serial.println("Door closed");
    reset();
    return;
   }

   if (start == 0) {
    Serial.println("Start new cycle");
    start = millis();
   }

   if (isFading()) {
    Serial.print("Fading ");
    float fade = fadeValue();
    Serial.print(fade);
    Serial.println(" %");
    allFade(fade);
    return;
   }

   if (isTimeout()) {
    Serial.println("Timeout");
    allOff();
    return;
   }

   Serial.println("Full");
   allFull();
}

bool doorOpen() {
  return digitalRead(DOOR_PIN) == HIGH;
}

bool isFading() {
  return (start + FADE_TIME) > millis();
}

bool isTimeout() {
  return (start + TIMEOUT) <= millis();
}

float fadeValue() {
  return ((float) (millis() - start)) / (float) FADE_TIME;
}

void topLightFade(float fadeValue) {
  int val = (int) (255 * fadeValue)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   ;
  analogWrite(TOPLIGHT_PIN, val);
}

void topLightFull() {
  analogWrite(TOPLIGHT_PIN, 255);
}

void topLightOff() {
  analogWrite(TOPLIGHT_PIN, 0);
}

void stripFade(float fadeValue) {
  int red = (int) (STRIP_RED * fadeValue);
  int green = (int) (STRIP_GREEN * fadeValue);
  int blue = (int) (STRIP_BLUE * fadeValue);
  uint32_t color = strip.Color(red, green, blue);
  strip.fill(color, 0, NUM_PIXELS);
  strip.show();
}

void stripOff() {
  strip.clear();
  strip.show();
}

void stripFull() {
  uint32_t color = strip.Color(STRIP_RED, STRIP_GREEN, STRIP_BLUE);
  strip.fill(color, 0, NUM_PIXELS);
  strip.show();
}

void allFade(float fadeValue) {
  topLightFade(fadeValue);
  stripFade(fadeValue);
}

void allOff() {
  topLightOff();
  stripOff();
}

void allFull() {
  topLightFull();
  stripFull();
}
