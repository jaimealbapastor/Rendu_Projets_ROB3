#include "morseTranslator.h"

/**
 * @brief Construct a new morse Translator::morse Translator object
 */
morseTranslator::morseTranslator()
{
}

/**
 * @brief Destroy the morse Translator::morse Translator object
 */
morseTranslator::~morseTranslator()
{
}

/**
 * @brief Get the code morse of a single character
 *
 * @param c : the char to translate
 * @return const char*
 */
const char *morseTranslator::_getMorse(char c)
{
  uint8_t i = 0;
  while (i < this->_nbOfChars)
  {
    if (this->_characters[i] == c)
      return this->_morseCode[i];
    i++;
  }
  return this->_nullMorse;
}

/**
 * @brief Get the morse code of a char array
 *
 * @param text : the char array to translate
 * @return char* : the pointer to the translated char array, ends with '\0'
 */
char *morseTranslator::translate(const char text[])
{
  uint16_t lengthText = 0;
  while (text[lengthText] != '\0') // calculate the length of the text
    lengthText++;

  const char *m;
  uint8_t morse_index = 0;
  uint16_t translation_index = 0;

  for (uint16_t text_index = 0; text_index < lengthText; text_index++)
  {
    if (text[text_index] == ' ')
      continue; // we will handle spaces only if there is text after it

    // === handle spaces ===
    if (text_index > 0)
    {
      // if the previous character is part of the word, add '...'
      if (text[text_index - 1] != ' ')
        for (uint8_t i = 0; i < 3; i++)
          this->_translation[translation_index++] = this->DOWN;

      // if the previous character was a space, add '.......'
      else if (text[text_index - 1] == ' ')
      {
        for (uint8_t i = 0; i < 7; i++)
          this->_translation[translation_index++] = this->DOWN;
      }
    }

    m = this->_getMorse(text[text_index]); // m only contains '.' and '-'
    morse_index = 0;

    while (*(m + morse_index) != '\0')
    {
      // this->_translation[translation_index] = *(m + morse_index);

      if (translation_index > 0 && this->_translation[translation_index - 1] == this->UP)
        this->_translation[translation_index++] = this->DOWN;

      if (*(m + morse_index) == this->DOWN)
      {
        this->_translation[translation_index++] = this->UP;
      }
      else
      {   // *(m + morse_index) = '-'
        for (uint8_t i = 0; i < 3; i++)
          this->_translation[translation_index++] = this->UP;
      }

      morse_index++;
    }
  }

  for (translation_index; translation_index < this->_translationLength; translation_index++)
    this->_translation[translation_index] = '\0';

  return this->_translation;
}
