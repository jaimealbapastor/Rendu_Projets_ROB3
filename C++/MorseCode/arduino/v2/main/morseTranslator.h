#ifndef MORSE_TRANSLATOR_H
#define MORSE_TRANSLATOR_H

#include <stdint.h>

class morseTranslator
{
private:
  static const uint8_t _nbOfChars = 62;
  const char _characters[_nbOfChars] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  // we save the morse code as '.-' instead of '=.===' because it requires less space
  const char *_morseCode[_nbOfChars] = {
      ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
      ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
      ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};

  const char _nullMorse[1] = {'\0'};

  static const uint16_t _translationLength = 200;
  char _translation[_translationLength];

  /**
   * @brief Get the code morse of a single character
   *
   * @param c : the char to translate
   * @return const char*
   */
  const char *_getMorse(char c);

public:
  // default: =
  char UP = '=';
  // default: .
  char DOWN = '.';

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
   * @return char* : the pointer to the translated char array, ends with '\0'
   */
  char *translate(const char text[]);
};

#endif
