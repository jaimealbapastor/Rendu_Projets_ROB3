// À utiliser dans le terminal c++
// https://www.onlinegdb.com/online_c++_compiler

#include <iostream>
#include "morseTranslator.h"
using namespace std;

morseTranslator morse;
char *s;

int main()
{
    s = morse.translate("Hello World");

    cout << "Traduction: ";
    while (*s != '\0')
    {
        cout << *s;
        s++;
    }
    return 0;
}
