#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"
#include "datastructure.h"
#include "dateutils.h"



TTeam* removeFromDVList(TTeam* pTeamToRemoveFromDVList, short(*compare)(const TTeam *, const TTeam *))
{
   unsigned short i;
   TTeam *pTempTeam;
   TTeam *pTeamRemovedFromDVList = NULL; // Entferntes Listenelement

//    if (pFirstTeamInDVList == NULL)
//        return NULL; // Leere Liste

   if (pFirstTeamInDVList == pLastTeamInDVList)
      pFirstTeamInDVList = pLastTeamInDVList = NULL; // Nur ein Element in der Liste
   else
      //pFirstTeamInDVList = pFirstTeamInDVList->pNextTeamInDVList; // Mindestens zwei Elemente in der Liste
   {
      for(pTempTeam = pFirstTeamInDVList; pTempTeam != pTeamToRemoveFromDVList; pTempTeam = pTempTeam->pNextTeamInDVList)
      {
         i++;
      }
      if(pTempTeam == pFirstTeamInDVList)
      {
         pFirstTeamInDVList->pNextTeamInDVList->pPreviousTeamInDVList = NULL;
         pFirstTeamInDVList = pFirstTeamInDVList->pNextTeamInDVList;
      }
      else if(pTempTeam == pLastTeamInDVList)
      {
         pLastTeamInDVList->pPreviousTeamInDVList->pNextTeamInDVList = NULL;
         pLastTeamInDVList = pLastTeamInDVList->pPreviousTeamInDVList;
      } else
      {
         pTempTeam->pPreviousTeamInDVList->pNextTeamInDVList = pTempTeam->pNextTeamInDVList;
         pTempTeam->pNextTeamInDVList->pPreviousTeamInDVList = pTempTeam->pPreviousTeamInDVList;
      }
   }
   return pTeamRemovedFromDVList;
}

int insertInDVList(TTeam * const pTeamToInsertInDVList, short(*compare)(const TTeam *, const TTeam *))
{
   TTeam *temp = pFirstTeamInDVList;

   pTeamToInsertInDVList->pNextTeamInDVList     = NULL;
   pTeamToInsertInDVList->pPreviousTeamInDVList = NULL;

   if (pFirstTeamInDVList == NULL)
   {
      pFirstTeamInDVList = pTeamToInsertInDVList;
      pLastTeamInDVList  = pTeamToInsertInDVList;
      return 1;
   }

   if (compare(pFirstTeamInDVList, pTeamToInsertInDVList) >= 0)
      //if (pFirstTeamInDVList->Index >= pTeamToInsertInDVList->Index)
   {
      pTeamToInsertInDVList->pNextTeamInDVList = pFirstTeamInDVList;
      pFirstTeamInDVList->pPreviousTeamInDVList = pTeamToInsertInDVList;
      pFirstTeamInDVList = pTeamToInsertInDVList;

      return 1;
   }
   if (compare(pLastTeamInDVList, pTeamToInsertInDVList) <= 0)
   {
      pLastTeamInDVList->pNextTeamInDVList = pTeamToInsertInDVList;
      pTeamToInsertInDVList->pPreviousTeamInDVList = pLastTeamInDVList;
      pLastTeamInDVList = pTeamToInsertInDVList;

      return 1;
   }

   while (temp->pNextTeamInDVList)
   {
      if(compare(pTeamToInsertInDVList, temp->pNextTeamInDVList) <= 0)
         // if((temp->pNextTeamInDVList)->Index > Neu->Index)
      {
         pTeamToInsertInDVList->pPreviousTeamInDVList = temp;
         pTeamToInsertInDVList->pNextTeamInDVList = temp->pNextTeamInDVList;
         temp->pNextTeamInDVList->pPreviousTeamInDVList = pTeamToInsertInDVList;
         temp->pNextTeamInDVList = pTeamToInsertInDVList;
         return 1;
      }

      temp = temp->pNextTeamInDVList;
   }

   return 0;
}


unsigned short appendInEVList(THashElement * const pHashElementToAppendInto, TTeam * pTeamOfPlayerToAppend, TPlayer * pPlayerToAppend, short(*compare)(const TPlayer *, const TPlayer *))
{
   TListElement *pListElementToAppend = calloc(1, sizeof(TListElement));
   TListElement *pTempListElement = pHashElementToAppendInto->pFirstListElement;

   pListElementToAppend->pTeam   = pTeamOfPlayerToAppend;
   pListElementToAppend->pPlayer = pPlayerToAppend;


   if((pHashElementToAppendInto->pFirstListElement == pHashElementToAppendInto->pLastListElement) && pHashElementToAppendInto->pFirstListElement == 0)
   {
      pHashElementToAppendInto->pFirstListElement  = pListElementToAppend;
      pHashElementToAppendInto->pLastListElement   = pListElementToAppend;

      return 1;

   } else if((pHashElementToAppendInto->pFirstListElement == pHashElementToAppendInto->pLastListElement) && pHashElementToAppendInto->pFirstListElement != 0)
   {
      if(compare(pHashElementToAppendInto->pFirstListElement->pPlayer, pListElementToAppend->pPlayer) >= 0)
      {
         pListElementToAppend->pNextListElement = pHashElementToAppendInto->pLastListElement;
         pHashElementToAppendInto->pFirstListElement = pListElementToAppend;
         //pHashElementToAppendInto->pLastListElement bleibt unveraendert, weil nur davor eingefuegt wurde
         return 1;

      } else
      {
         //pListElementToAppend->pPreviousListElement = pHashElementToAppendInto->pFirstListElement;
         pHashElementToAppendInto->pFirstListElement->pNextListElement = pListElementToAppend;
         pHashElementToAppendInto->pLastListElement = pListElementToAppend;

         return 1;
      }

   } else
   {
      while(pTempListElement->pNextListElement)
      {
         if(compare(pTempListElement->pNextListElement->pPlayer, pListElementToAppend->pPlayer) >= 0)
         {
            pListElementToAppend->pNextListElement = pTempListElement->pNextListElement;
            pTempListElement->pNextListElement = pListElementToAppend;
            return 1;
         }

         pTempListElement = pTempListElement->pNextListElement;
      }

      if(compare(pHashElementToAppendInto->pLastListElement->pPlayer, pListElementToAppend->pPlayer) <= 0)
      {
         pHashElementToAppendInto->pLastListElement = pListElementToAppend;
         pTempListElement->pNextListElement = pListElementToAppend;
         return 1;
      } else
         assert(0);
   }
   assert(0);

   return 0;
}

unsigned short deleteFromEVList(THashElement * const pHashElementToDeleteFrom, TPlayer * pPlayerToDelete)
{
   TListElement *pTempListElement = pHashElementToDeleteFrom->pFirstListElement;

   if(pHashElementToDeleteFrom->pFirstListElement->pPlayer == pPlayerToDelete && pHashElementToDeleteFrom->pLastListElement->pPlayer == pPlayerToDelete)
   {
      pHashElementToDeleteFrom->pFirstListElement = NULL;
      pHashElementToDeleteFrom->pLastListElement  = NULL;
      return 1;
   }

   if(pHashElementToDeleteFrom->pFirstListElement->pPlayer == pPlayerToDelete)
   {
      pHashElementToDeleteFrom->pFirstListElement = pHashElementToDeleteFrom->pFirstListElement->pNextListElement;
      return 1;
   }

   while(pTempListElement->pNextListElement)
   {
      if(pPlayerToDelete == pTempListElement->pNextListElement->pPlayer)
      {
         pTempListElement->pNextListElement = pTempListElement->pNextListElement->pNextListElement;
         return 1;
      }
      pTempListElement = pTempListElement->pNextListElement;
   }

   return 0;
}
