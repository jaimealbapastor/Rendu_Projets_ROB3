#ifndef MORSE_TRANSLATOR_H
#define MORSE_TRANSLATOR_H

#include <stdint.h>

class morseTranslator
{
  private:

    static const uint8_t nbOfChars = 63;
    const char characters[nbOfChars] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' '
                                       };
    const char *morseCode[nbOfChars] = {
      ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
      ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
      ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----", " "
    };

    static const uint8_t morseLength = 6;
    const char nullMorse[1] = {'\0'};

    static const uint16_t translationLength = morseLength * 20;
    char translation[translationLength];

    const char *getMorse(char c);

  public:
    morseTranslator();
    ~morseTranslator();

    /**
       @brief translates text into morse code

       @param text the sentence to translate
       @return char* containing the char list representing morse
    */
    char *translate(const char text[], bool spacesBetweenLetters = true);
};
#endif
