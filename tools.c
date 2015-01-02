#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "database.h"
#include "tools.h"
#include "escapesequenzen.h"


extern void printErrorMessage()
{
   printf("Ungueltige Eingabe\n");
}

extern short getText(char const *pPrompt, unsigned short maxLengthOfUserInput, unsigned short allowEmptyText, char **ppReturnString)
{
    char scanfFormatAsString[20];                                   // Inhalt sieht nachher beispielsweise so aus (bei maxLengthOfUserInput = 15): "%15[^\n]"
    unsigned short successfullScanf;
    unsigned short doContinue = 1;                                    // Schleife wird solange ausgeführt, bis continue = 0 ist.
    unsigned short lengthOfUserInput;                               // Länge der vom Benutzer eingegebenen Zeichenkette
    char *pUserInput = calloc(maxLengthOfUserInput + 1, sizeof(char));

    if (pUserInput != NULL)
    {
        sprintf(scanfFormatAsString, "%%%hu[^\n]", maxLengthOfUserInput);
        do
        {
            printf("%s", pPrompt);
            successfullScanf = scanf(scanfFormatAsString, pUserInput);
            clearBuffer(); // Notwendig?

            lengthOfUserInput = strlen(pUserInput);
            if (successfullScanf == 1)
            {
                if (lengthOfUserInput > 0)
                {
                    if (lengthOfUserInput < maxLengthOfUserInput)
                    {
                        *ppReturnString = calloc(lengthOfUserInput + 1, sizeof(char));
                                                                   // Für den String wird genau so viel Speicher reserviert, wie nötig ist.
                        if (*ppReturnString != NULL)
                        {
                            doContinue= 0;                               // Schleife verlassen
                            strcpy(*ppReturnString, pUserInput);                    // Benutzereingabe in das "zurückzugebende" Argumgent kopieren
                        }
                        else
                        {
                            free(pUserInput);
                            assert(*ppReturnString == NULL);
                            return 0;                                   // Es konnte kein Speicher reserviert werden
                        }
                    } else
                    {
                        printf("\nInfo: Bitte geben Sie maximal %u Zeichen ein\n\n", maxLengthOfUserInput);
                    }
                }
                else
                {
                                                                    // Der Benutzer hat nur die Eingabetaste gedrückt.
                    if (allowEmptyText != 0)
                        doContinue = 0;                               // emptyness is allowed. break loop
                }
            }
            else
            {
                if (lengthOfUserInput == 0 && allowEmptyText != 0)
                {
                    doContinue = 0;                                   // emptyness is allowed. break loop
                    *ppReturnString = NULL;                               // Ist gültig, da dieser Punkt nur erreicht werden kann, wenn allowEmptyText = 1 ist.
                }
            }
        } while (doContinue != 0);
    }
    else
        return 0;                                                   // Speicher konnte nicht reserviert werden

    free(pUserInput);

    return 1;                                                       // Alles ok
}

extern short getNumber(char const *pPrompt, unsigned short *ppReturnNumber, unsigned short lowestNumberAllowed, unsigned short highesNumberAllowed)
{
    unsigned short successfullScanf;
    unsigned short doContinue = 1;
    unsigned short maxDigits = 3;
    unsigned short lengthOfUserInput;
    unsigned short userInputAsUnsignedShort;
    char pUserInput[3];
    char scanfFormatAsString[20];


    sprintf(scanfFormatAsString, "%%%hu[^\n]", maxDigits);

    do
    {
        printf("%s", pPrompt);
        successfullScanf = scanf(scanfFormatAsString, pUserInput);
        clearBuffer();


        lengthOfUserInput = strlen(pUserInput);
        if (successfullScanf == 1)
        {
            if (lengthOfUserInput > 0)
            {
                userInputAsUnsignedShort = atoi(pUserInput);

                if (userInputAsUnsignedShort >= lowestNumberAllowed && userInputAsUnsignedShort <= highesNumberAllowed)
                {
                    *ppReturnNumber = userInputAsUnsignedShort;
                    doContinue = 0;
                } else
                {
                    printf("\nInfo: Bitte geben Sie nur Zahlen zwischen %u und %u ein\n\n", lowestNumberAllowed, highesNumberAllowed);
                }
            }
        }
    } while (doContinue != 0);

    return 1;
}

extern short askPolarQuestion(char * pPrompt)
{
    int readSuccessfully;
    char userInput;

    do
    {
        printf("%s", pPrompt);

// Benutzereingabe einlesen

    readSuccessfully = scanf("%c", &userInput); // Ein Zeichen einlesen
    if (userInput != '\n')
    {
        clearBuffer();
    }

// UserInput überprüfen
    if (readSuccessfully != 1)
    {
        printErrorMessage(); // Fehlermeldung hinter dem Eingabecursor ausgeben
    }else
    {
// Gültige Antworten auf die Frage sind 'j', 'J', 'n' und 'N'.
        switch (userInput)
        {
            case 'j':
            case 'J':
               return 1;

            case 'n':
            case 'N':
               return 0;

            default:
               printErrorMessage(); // Fehlermeldung hinter dem UserInputcursor ausgeben
         }
      }
    }while (1);

   // Wird nie erreicht:
   return 0; // Nur um den Compiler zu beruhigen
}

extern short askAgain()
{
   int readSuccessfully;
   char userInput;

   do
   {
      printf("Moechten Sie noch einmal (j/n)? ");

      readSuccessfully = scanf("%c", &userInput);
      if (userInput != '\n')
      {
         clearBuffer();
      }

      if (readSuccessfully != 1)
      {
         continue;
      } else
      {
         switch (userInput)
         {
            case 'j':
            case 'J':   return 1;
            case 'n':
            case 'N':   return 0;

            default:    break;
         }
      }
   } while (1);

   // Wird nie erreicht:
   return 0; // Nur um den Compiler zu beruhigen
}

extern void clearBuffer()
{
	char Dummy;
	do
	{
		scanf("%c", &Dummy);
	} while (Dummy != '\n');

}

extern void clearScreen()
{
   system("clear");
}

extern void waitForEnter()
{
    char buffer[2];

    printf("\nBitte Eingabetaste (Enter) druecken ...");
    scanf("%1[^\n]", buffer);
    clearBuffer();
}

extern void printLine(char printChar, unsigned long lineLength)
{
    unsigned short i;

    for(i = 0; i < lineLength; i++)
        printf("%c", printChar);

    printf("\n");
}

extern short terminateApplication()
{
    if(saveTeams("teams.db") == 0)
        return 0;
    else
    {
        printf("\n Datenbank konnte nicht geschrieben werden! \n");
        waitForEnter();
    }
    return 1;
}
