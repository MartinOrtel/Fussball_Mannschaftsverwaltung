#include <stdio.h>

#include "datastructure.h"
#include "tools.h"


unsigned short calcDivisionRemainder(char *pText)
{
    unsigned short sum = 0;

    while(*pText)
    {
        //großkleinschreibung Einbauen
        sum += *pText;
        pText++;
    }

    return sum % MAXINDEX;
}

TListElement *searchForPlayer(THashElement *aIndex, short (*compare)(const TPlayer *, const TPlayer *), const TPlayer *pPlayerSearchedFor)
{
   unsigned short hashValue;
   TListElement *pTempListElement = NULL;


   hashValue = calcDivisionRemainder(pPlayerSearchedFor->nameOfPlayer);

   pTempListElement = ( aIndex + hashValue )->pFirstListElement;

   while(pTempListElement)
   {
      if(compare(pTempListElement->pPlayer, pPlayerSearchedFor) == 0)
         return pTempListElement;

      pTempListElement = pTempListElement->pNextListElement;
   }

   return NULL;
}
