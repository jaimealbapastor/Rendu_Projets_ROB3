#ifndef STDINT_H
#define STDINT_H
#include <stdint.h>
#endif

#ifndef MORSE_TRANSLATOR_H
#define MORSE_TRANSLATOR_H

class morseTranslator
{
private:
    static const uint8_t morseLength = 6;
    const char blankSpace = '\0';

    static const int translationLength = morseLength * 1024;
    char translation[translationLength];

    char dic[127][morseLength];

    void addMorseToDic(char c, const char morse[]);
    char* getMorse(char c);

public:
    morseTranslator();
    ~morseTranslator();

    /**
     * @brief translates text into morse code
     *
     * @param text the sentence to translate
     * @return char* containing the char list representing morse
     */
    char *translate(const char text[]);
};
#endif
