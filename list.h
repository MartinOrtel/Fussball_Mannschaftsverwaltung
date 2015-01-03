#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "datastructure.h"


TTeam* removeFromDVList(TTeam* pTeamToRemoveFromDVList, short(*compare)(const TTeam *, const TTeam *));

int insertInDVList(TTeam * const pTeamToInsertInDVList, short(*compare)(const TTeam *, const TTeam *));

unsigned short appendInEVList(THashElement * const pHashElementToAppendInto, TTeam * pTeamOfPlayerToAppend, TPlayer * pPlayerToAppend, short(*compare)(const TPlayer *, const TPlayer *));

unsigned short deleteFromEVList(THashElement * const pHashElementToDeleteFrom, TPlayer * pPlayerToDelete);


#endif // LIST_H_INCLUDED
