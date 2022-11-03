#include <iostream>
#include "morseTranslator.h"
using namespace std;

int main()
{
    morseTranslator morse;
    char *s;

    s = morse.translate("a");

    while (*s != '\0')
    {
        cout << *s;
    }
    return 0;
}
