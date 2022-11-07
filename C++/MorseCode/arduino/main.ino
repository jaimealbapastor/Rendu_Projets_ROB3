#include "morseTranslator.h"

const char DOT = '.';
const int DOT_DELAY = 1000; // in milliseconds
const char MINUS = '-';
const int MINUS_DELAY = 2000;   // in milliseconds
const int INTERVAL = 1000;  // in milliseconds

morseTranslator morse;
char *translation;

int availableBytes;

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}
void loop(){

    availableBytes = Serial.available();

    if (availableBytes){

        char input[availableBytes];
        for (int i = 0; i< availableBytes; i++){
            input[i]= Serial.read();
        }

        translation = morse.translate(input, true);
        Serial.println(input);
        Serial.print('Translation: ');
        Serial.println(translation);

        while (*translation!='\0'){
            if (*translation == DOT){
                digitalWrite(LED_BUILTIN, HIGH);
                delay(DOT_DELAY);
                digitalWrite(LED_BUILTIN, LOW);
                delay(INTERVAL);
            }else if (*translation == MINUS)
            {
                digitalWrite(LED_BUILTIN, HIGH);
                delay(MINUS_DELAY);
                digitalWrite(LED_BUILTIN, LOW);
                delay(INTERVAL);
            }

            translation++;
        }
        availableBytes = 0;
    }
}
