#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "dateutils.h"
#include "datastructure.h"


static short isLeapYear(int year)
{
   if (year % 400 == 0)
   {
      return 1;
   } else if (year % 4 == 0 && year % 100 != 0)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

static short isDateValid(TDate const * pDate)
{
   if (pDate->day < 1)
   {
      return 0;
   }

   if (pDate->year < 1582)     // Der Gregorianische Kalender beginnt erst ab dem Jahr 1582
   {
      return 0;
   }

   switch (pDate->month)
   {
   case 2:
      if (isLeapYear(pDate->year) == 1)
         if (pDate->day > 29)
            return 0;

      if (pDate->day > 28)
         return 0;

      break;

   case 1:
   case 3:
   case 5:
   case 7:
   case 8:
   case 10:
   case 12:

      if (pDate->day > 31)
         return 0;

      break;

   case 4:
   case 6:
   case 9:
   case 11:

      if (pDate->day > 30)
         return 0;

      break;

   default:
      return 0; // Ungültiger Monat
   }

   return 1;
}

extern short getDateFromString(char const *pUserInput, TDate *pReturnDate)
{
   char *pDayAsString = NULL, *pMonthAsString = NULL, *pYearAsString = NULL;                       // Tag, Monat, Jahr als Teilstring von pUserInput
   TDate TempDate;                                                          // Damit das übergebene pUserInput im Fehlerfall nicht verändert werden muss.
   unsigned short countOfDots = 0;                                           // Es dürfen maximal zwei Punkte vorkommen
   char *pLocalDate;                                                          // lokales Datum ( = datum-Parameter)
   char *p ;                                                               // Iterator


   // Datum kopieren, damit der datum-Parameter nicht verändert werden muss.

   pLocalDate = calloc(strlen(pUserInput) + 1, sizeof(char));
   if (pLocalDate == NULL)
      return 0;


   p = pLocalDate;
   strncpy(pLocalDate, pUserInput, strlen(pUserInput));


   while (*p != '\0')
   {
      if (*p >= '0' && *p <= '9')
      {
         if (pDayAsString == NULL)
            pDayAsString = p;                                                   // Der Tag ist noch nicht gesetzt. Er kommt als erstes.
         else if (pMonthAsString == NULL)
            pMonthAsString = p;                                                 // Der Monat ist noch nicht gesetzt. Er kommt als zweites.
         else if (pYearAsString == NULL)
            pYearAsString = p;                                                  // Das Jahr ist noch nicht gesetzt. Es kommt als letztes.
         else
         {
            free(pLocalDate);
            return 0;
         }

         while ((*(p + 1) >= '0' && *(p + 1) <= '9') && *(p + 1) != '\0')// Die Zahl bis zum Ende durchlaufen
            ++p;
      }
      else if (*p == '.')
      {
         ++countOfDots;
         *p = '\0';                                                      // Punkte werden durch \0 ersetzt.
      }
      else
      {
         free(pLocalDate);
         return 0;                                                       // Es ist ein ungltiges Zeichen enthalten.
      }

      ++p;
   }

   if (pDayAsString == NULL || pMonthAsString == NULL || pYearAsString == NULL)
   {
      free(pLocalDate);
      return 0;                                                           // Tag, Monat und Jahr müssen im Datum enthalten sein.
   }
   if (countOfDots != 2)
   {
      free(pLocalDate);
      return 0;                                                           // Es müssen genau zwei Punkte vorkommen
   }

   // Die Typecast (int -> unsigned short) sollten immer funktionieren,
   // da für Tag, Monat und Jahr eh nur kleine positive Zahlen zulässig sind.
   TempDate.day   = atoi(pDayAsString);    /* if (errno != 0) //return 0;*/
   TempDate.month = atoi(pMonthAsString);  /* if (errno != 0) //return 0;*/
   TempDate.year  = atoi(pYearAsString);   /* if (errno != 0) //return 0;*/

   // Zur Sicherheit

   if (isDateValid(&TempDate) == 0)
      return 0;

   pReturnDate->day   = TempDate.day;
   pReturnDate->month = TempDate.month;
   pReturnDate->year  = TempDate.year;
   //date->dayOfWeek = getDayOfWeek(date);

   free(pLocalDate);

   return 1;
}

extern short getDate(char const *pPrompt, TDate **ppReturnDate)
{
   char aUserInput[12];
   int numberOfSuccessfullyReadValues;
   TDate * pTempDate;

   printf("%s", pPrompt);

   numberOfSuccessfullyReadValues = scanf("%11[^\n]", aUserInput);
   clearBuffer();

   if (numberOfSuccessfullyReadValues == 1)
   {
      pTempDate = calloc(1, sizeof(TDate));

      if (getDateFromString(aUserInput, pTempDate) == 1)
      {
         *ppReturnDate = calloc(1, sizeof(TDate));
         if (*ppReturnDate)
         {
            (*ppReturnDate)->day        = (*pTempDate).day;
            (*ppReturnDate)->month      = (*pTempDate).month;
            (*ppReturnDate)->year       = (*pTempDate).year;
            //(*ppReturnDate)->dayOfWeek  = (*tmpDate).dayOfWeek;

            free(pTempDate);

            return 1;
         }
      }
   }

   return 0;
}
