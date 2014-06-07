#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "menu.h"
#include "tools.h"


short getMenu(char const *title, char const **menuPoints, unsigned short numMenuPoints)
{
    unsigned short i; // Zählvariable
    unsigned short input; // Benutzereingabe
    int scanfRet = 0;

    // Abbrechen, falls NULL-Pointer übergeben wurden.
    assert(title);
    assert(numMenuPoints);
    assert(menuPoints);

    do
    {
        clearScreen();
        printf("%s\n", title);
        printLine('=', strlen(title));
        printf("\n");

        for (i = 0; i < numMenuPoints; ++i)
            printf("%2u. %s\n", i + 1, menuPoints[i]);

        printf("\nIhre Wahl: ");
        scanfRet = scanf("%hu", &input);
        clearBuffer();
    } while (scanfRet != 1 || input < 1 || input > numMenuPoints);

    return input;
}
