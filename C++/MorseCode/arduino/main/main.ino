#ifndef STDINT_H
#define STDINT_H
#include <stdint.h>
#endif

#include "morseTranslator.h"

// ====== LED =======
const char DOT = '.';
const char MINUS = '-';
int8_t stateOfLed = 0;
// === Intervals ====
const uint16_t DOT_DELAY = 500; // in milliseconds
const uint16_t MINUS_DELAY = 1000;   // in milliseconds
const uint16_t INTERVAL = 750;  // in milliseconds
// ===== Timer ======
unsigned long startMillis;
unsigned long currentMillis;
uint16_t timeToWait = 0;
int8_t ongoingBlinking = false;
// ===== Morse ======
morseTranslator MT;
char* translation = nullptr;
uint8_t translation_index = 0;
char currentChar;
uint8_t incomingBytes = 0;
// ==================

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  startMillis = millis();

  Serial.println("==== Ready to translate ====");
}

void loop() {


  if (Serial.available()) {
    delay(30); // wait for the data to arrive

    incomingBytes = Serial.available();
    char input[incomingBytes + 1];

    for (uint8_t i = 0; i < incomingBytes; i++) {
      input[i] = Serial.read();
    }
    // at the end of the text typed there is one more character: 10 -> LineFeed
    // so we have to add a Null Char ('\0') to detect the end of the char array
    input[incomingBytes] = '\0';

    Serial.print("Input:\t");
    Serial.println(input);

    // ==================

    translation = MT.translate(input, true);
    Serial.print("Morse:\t");
    Serial.println(translation);
    translation_index = 0; // start blinking
  }

  if (translation != nullptr and * (translation + translation_index) != '\0') {
    ongoingBlinking = true;
    currentMillis = millis();
    currentChar = * (translation + translation_index);

    if (currentChar != DOT and currentChar != MINUS) {
      translation_index++;
    } else if (currentMillis - startMillis >= timeToWait) {
      if (stateOfLed) { // add an interval between two blinks
        timeToWait = INTERVAL;
      } else {
        Serial.print("translation[");
        Serial.print(translation_index);
        Serial.print("] = ");
        Serial.println(currentChar);
        if (currentChar == DOT) {
          timeToWait = DOT_DELAY;
          translation_index++;
        } else if (currentChar == MINUS) {
          timeToWait = MINUS_DELAY;
          translation_index++;
        }
      }

      stateOfLed = -stateOfLed + 1;
      digitalWrite(LED_BUILTIN, stateOfLed);
      startMillis = currentMillis;

      Serial.print("Waiting ");
      Serial.print(timeToWait);
      Serial.print(" msec in state ");
      Serial.println(stateOfLed);
    }

  } else {
    if (ongoingBlinking and millis() - startMillis >= timeToWait) {
      ongoingBlinking = false;
      stateOfLed = 0;
      digitalWrite(LED_BUILTIN, stateOfLed);
      Serial.println("Returning to state 0");
    }
  }
}
