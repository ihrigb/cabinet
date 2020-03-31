/*
  Fading

  This example shows how to fade an LED using the analogWrite() function.

  The circuit:
  - LED attached from digital pin 9 to ground.

  created 1 Nov 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fading
*/

int DOOR_PIN = 1;
int TOPLIGHT_PIN = 3;

unsigned long fadeTime = 5000;    // 5 seconds
unsigned long timeout = 120000;   // 2 minutes

unsigned long start;

void setupPins() {
  pinMode(DOOR_PIN, INPUT);
}

void reset() {
  allOff();
  start = 0;
}

void setup() {
  setupPins();
  reset();
}

void loop() {
   if (!doorOpen()) {
    reset();
    return;
   }

   if (start == 0) {
    start = millis();
   }

   if (isFading()) {
    float fade = fadeValue();
    allFade(fade);
    return;
   }

   if (isTimeout()) {
    allOff();
    return;
   }

   allFull();
}

bool doorOpen() {
  return digitalRead(DOOR_PIN) == HIGH;
}

bool isFading() {
  return (start + fadeTime) > millis();
}

bool isTimeout() {
  return (start + timeout) <= millis();
}

float fadeValue() {
  return ((start + fadeTime) - millis()) / fadeTime;
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

void allFade(float fadeValue) {
  topLightFade(fadeValue);
}

void allOff() {
  topLightOff();
}

void allFull() {
  topLightFull();
}
