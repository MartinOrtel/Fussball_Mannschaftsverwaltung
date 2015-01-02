#include <stdio.h>
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

    pTeamToInsertInDVList->pNextTeamInDVList = NULL;
    pTeamToInsertInDVList->pPreviousTeamInDVList  = NULL;

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
