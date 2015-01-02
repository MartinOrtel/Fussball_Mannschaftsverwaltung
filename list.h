#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "datastructure.h"

TTeam* removeFromDVList(TTeam* pTeamToRemoveFromDVList, short(*compare)(const TTeam *, const TTeam *));

int insertInDVList(TTeam * const pTeamToInsertInDVList, short(*compare)(const TTeam *, const TTeam *));

#endif // LIST_H_INCLUDED
