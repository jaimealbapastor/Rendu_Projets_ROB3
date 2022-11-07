#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#include "morseTranslator.h"
using namespace std;

morseTranslator morse;

int main()
{

    char *s;

    s = morse.translate("a b c");

    cout << "Traduction: ";
    while (*s != '\0')
    {
        cout << *s;
        s++;
    }
    return 0;
}
