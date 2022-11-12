#include "morseTranslator.h"

morseTranslator::morseTranslator()
{
}

morseTranslator::~morseTranslator()
{
}

const char *morseTranslator::getMorse(char c)
{
  uint8_t i = 0;
  while (i < this->nbOfChars)
  {
    if (this->characters[i] == c) return this->morseCode[i];
    i++;
  }
  return this->nullMorse;
}

char *morseTranslator::translate(const char text[], bool spacesBetweenLetters)
{
  uint16_t lengthText = 0;
  while (text[lengthText] != '\0')
    lengthText++;

  const char* m;

  int translation_index = 0;
  int morse_index = 0;

  for (uint16_t text_index = 0; text_index < lengthText; text_index++)
  {
    // strcpy(m, this->getMorse(text[text_index]));
    m = this->getMorse(text[text_index]);

    morse_index = 0;
    while (*(m + morse_index) != '\0')
    {
      this->translation[translation_index] = *(m + morse_index);
      translation_index++;
      morse_index++;
    }

    if (spacesBetweenLetters) {
      this->translation[translation_index] = ' ';
      translation_index++;
    }
  }

  for (translation_index; translation_index < this->translationLength; translation_index++)
    this->translation[translation_index] = '\0';

  return this->translation;
}
