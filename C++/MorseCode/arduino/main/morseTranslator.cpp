#include "morseTranslator.h"

/**
 * @brief Construct a new morse Translator::morse Translator object
 */
morseTranslator::morseTranslator() {
}

/**
 * @brief Destroy the morse Translator::morse Translator object
 */
morseTranslator::~morseTranslator() {
}

/**
 * @brief Get the code morse of a single character
 * 
 * @param c : the char to translate
 * @return const char*
 */
const char *morseTranslator::_getMorse(char c) {
  uint8_t i = 0;
  while (i < this->_nbOfChars) {
    if (this->_characters[i] == c) return this->_morseCode[i];
    i++;
  }
  return this->nullMorse;
}

/**
 * @brief Get the morse code of a char array
 * 
 * @param text : the char array to translate
 * @param spacesBetweenLetters (optional) : bool value to add spaces between letters in the returned translation
 * @return char* : the pointer to the translated char array, ends with '\0'
 */
char *morseTranslator::translate(const char text[], bool spacesBetweenLetters) {
  uint16_t lengthText = 0;
  while (text[lengthText] != '\0')
    lengthText++;

  const char *m;

  int translation_index = 0;
  int morse_index = 0;

  for (uint16_t text_index = 0; text_index < lengthText; text_index++) {
    // strcpy(m, this->getMorse(text[text_index]));
    m = this->_getMorse(text[text_index]);

    morse_index = 0;
    while (*(m + morse_index) != '\0') {
      this->_translation[translation_index] = *(m + morse_index);
      translation_index++;
      morse_index++;
    }

    if (spacesBetweenLetters) {
      this->_translation[translation_index] = ' ';
      translation_index++;
    }
  }

  for (translation_index; translation_index < this->_translationLength; translation_index++)
    this->_translation[translation_index] = '\0';

  return this->_translation;
}
