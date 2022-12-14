#include "morseTranslator.h"

void morseTranslator::addMorseToDic(char c, const char morse[])
{

    int length = 0;
    while (morse[length] != '\0')
        length++;

    int i = 0;
    while (i < this->morseLength)
    {
        if (i < length)
            this->dic[c][i] = morse[i];
        else
            this->dic[c][i] = this->blankSpace;
        i++;
    }
}

morseTranslator::morseTranslator()
{
    this->addMorseToDic('a', ".-");
    this->addMorseToDic('b', "-...");
    this->addMorseToDic('c', "-.-.");
    this->addMorseToDic('d', "-..");
    this->addMorseToDic('e', ".");
    this->addMorseToDic('f', "..-.");
    this->addMorseToDic('g', "--.");
    this->addMorseToDic('h', "....");
    this->addMorseToDic('i', "..");
    this->addMorseToDic('j', ".---");
    this->addMorseToDic('k', "-.-");
    this->addMorseToDic('l', ".-..");
    this->addMorseToDic('m', "--");
    this->addMorseToDic('n', "-.");
    this->addMorseToDic('o', "---");
    this->addMorseToDic('p', ".--.");
    this->addMorseToDic('q', "--.-");
    this->addMorseToDic('r', ".-.");
    this->addMorseToDic('s', "...");
    this->addMorseToDic('t', "-");
    this->addMorseToDic('u', "..-");
    this->addMorseToDic('v', "...-");
    this->addMorseToDic('w', ".--");
    this->addMorseToDic('x', "-..-");
    this->addMorseToDic('y', "-.--");
    this->addMorseToDic('z', "--..");
    this->addMorseToDic('A', ".-");
    this->addMorseToDic('B', "-...");
    this->addMorseToDic('C', "-.-.");
    this->addMorseToDic('D', "-..");
    this->addMorseToDic('E', ".");
    this->addMorseToDic('F', "..-.");
    this->addMorseToDic('G', "--.");
    this->addMorseToDic('H', "....");
    this->addMorseToDic('I', "..");
    this->addMorseToDic('J', ".---");
    this->addMorseToDic('K', "-.-");
    this->addMorseToDic('L', ".-..");
    this->addMorseToDic('M', "--");
    this->addMorseToDic('N', "-.");
    this->addMorseToDic('O', "---");
    this->addMorseToDic('P', ".--.");
    this->addMorseToDic('Q', "--.-");
    this->addMorseToDic('R', ".-.");
    this->addMorseToDic('S', "...");
    this->addMorseToDic('T', "-");
    this->addMorseToDic('U', "..-");
    this->addMorseToDic('V', "...-");
    this->addMorseToDic('W', ".--");
    this->addMorseToDic('X', "-..-");
    this->addMorseToDic('Y', "-.--");
    this->addMorseToDic('Z', "--..");
    this->addMorseToDic('1', ".----");
    this->addMorseToDic('2', "..---");
    this->addMorseToDic('3', "...--");
    this->addMorseToDic('4', "....-");
    this->addMorseToDic('5', ".....");
    this->addMorseToDic('6', "-....");
    this->addMorseToDic('7', "--...");
    this->addMorseToDic('8', "---..");
    this->addMorseToDic('9', "----.");
    this->addMorseToDic('0', "-----");
    this->addMorseToDic(' ', " ");
}

morseTranslator::~morseTranslator()
{
}

char *morseTranslator::getMorse(char c)
{
    return this->dic[c];
}

char *morseTranslator::translate(const char text[], const bool spacesBetweenLetters = false)
{
    int lengthText = 0;
    while (text[lengthText] != '\0')
        lengthText++;

    const int lengthTranslation = lengthText * this->morseLength;
    // char translation[lengthTranslation]; -> storage size of 'translation' isn't constant

    char *c;
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < lengthText)
    {
        c = this->getMorse(text[i]);

        k = 0;
        while (c[k] != this->blankSpace)
        {
            this->translation[j] = *(c + k);
            j++;
            k++;
        }

        if (spacesBetweenLetters){
            this->translation[j] = ' ';
            j++;
            k++;
        }

        i++;
    }
    for (j; j < this->translationLength; j++)
        this->translation[j] = this->blankSpace;

    return this->translation;
}

char* morseTranslator::getLastTranslation(){
    return this->translation;
}
