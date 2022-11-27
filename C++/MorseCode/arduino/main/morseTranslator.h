#ifndef MORSE_TRANSLATOR_H
#define MORSE_TRANSLATOR_H

#include <stdint.h>

class morseTranslator {
private:
  static const uint8_t nbOfChars = 63;
  const char characters[nbOfChars] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                       'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                       '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ' };
  const char *morseCode[nbOfChars] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
    ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----", " "
  };

  static const uint8_t morseLength = 6;
  const char nullMorse[1] = { '\0' };

  static const uint16_t translationLength = morseLength * 20;
  char translation[translationLength];

  /**
   * @brief Get the code morse of a single character
   *
   * @param c : the char to translate
   * @return const char*
   */
  const char *getMorse(char c);

public:
  /**
   * @brief Construct a new morse Translator::morse Translator object
   */
  morseTranslator();
  /**
   * @brief Destroy the morse Translator::morse Translator object
   */
  ~morseTranslator();

  /**
   * @brief Get the morse code of a char array
   *
   * @param text : the sentence [char array] to translate
   * @param spacesBetweenLetters (optional) : bool value to add spaces between letters in the returned translation
   * @return char* : the pointer to the translated char array, ends with '\0'
   */
  char *translate(const char text[], bool spacesBetweenLetters = true);
};
#endif
