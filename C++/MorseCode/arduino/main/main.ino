#include <stdint.h>
#include "morseTranslator.h"

// ====== LED =======
const char DOT = '.';
const char MINUS = '-';
int8_t stateOfLed = 0;
// === Intervals ====
const uint16_t DOT_DELAY = 500;     // in milliseconds
const uint16_t MINUS_DELAY = 1000;  // in milliseconds
const uint16_t INTERVAL = 750;      // in milliseconds
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

  if (Serial.available() && !ongoingBlinking) {  // wait to finish the previous blinking
    delay(30);                                   // wait for the data to arrive

    incomingBytes = Serial.available();

    // at the end of the text typed there is one more character: 10 -> LineFeed
    // so we have to add a Null Char ('\0') to detect the end of the char array
    char input[incomingBytes + 1];  // +1 to add the '/0' char at the end

    for (uint8_t i = 0; i < incomingBytes; i++) {
      input[i] = Serial.read();
      if (input[i] == 10) input[i] = ' ';  // get rid of the 'line feed' because it's not pretty on display (but the code works anyway)
    }
    input[incomingBytes] = '\0';

    Serial.print("Input:\t");
    Serial.println(input);

    // ===Translation====
    translation = MT.translate(input, true);  // MT.translate returns the pointer of the translation (which is a class variable)
    Serial.print("Morse:\t");
    Serial.println(translation);
    translation_index = 0;  // start blinking at the beginning of the translation
  }

  if (translation != nullptr and *(translation + translation_index) != '\0') {  // if the translation exists

    ongoingBlinking = true;  // don't interrupt while ongoingBlinking
    currentMillis = millis();
    currentChar = *(translation + translation_index);

    if (currentChar != DOT && currentChar != MINUS) {  // skip ' ' and '\0'
      translation_index++;

    } else if (currentMillis - startMillis >= timeToWait) {

      if (stateOfLed) {         // if the state of the led was 1
        timeToWait = INTERVAL;  // just add an interval between two blinks

      } else {  // if the state of the led was 0

        translation_index++;  // go to next char of the translation

        if (currentChar == DOT) {
          timeToWait = DOT_DELAY;
        } else if (currentChar == MINUS) {
          timeToWait = MINUS_DELAY;
        }

        Serial.print("\nchar nº");
        Serial.print(translation_index);
        Serial.print("-> ");
        Serial.print(currentChar);
      }

      stateOfLed = -stateOfLed + 1;  // change the state of the led
      digitalWrite(LED_BUILTIN, stateOfLed);
      startMillis = currentMillis;

      Serial.print("\t");
      Serial.print(timeToWait);
      Serial.print("ms in ");
      Serial.print(stateOfLed);
    }

  } else if (ongoingBlinking && millis() - startMillis >= timeToWait) {  // if we arrive at the end of the translation
    ongoingBlinking = false;                                             // now we can start another blinking
    stateOfLed = 0;                                                      // and we restart the state of the led
    digitalWrite(LED_BUILTIN, stateOfLed);
    Serial.println("\nReturning to state 0\n");
  }
}