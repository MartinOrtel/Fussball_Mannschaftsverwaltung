#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED
#include "datastructure.h"


//int partition(TPlayer *pPlayersToSort,  short ui,  short oi, short(*compare)(const TPlayer *, const TPlayer *));
//void internQuickSortPlayers(TPlayer *pPlayersToSort,  short ui,  short oi, short(*compare)(const TPlayer *, const TPlayer *));   //short (*compare)(TAppointment const*, TAppointment const*), void (*swapApps)(TAppointment*, TAppointment*))
void quickSortPlayers(short (*compare)(const TPlayer *, const TPlayer *));

short compareTeams(const TTeam *pFirstTeamToCompare, const TTeam *pSecondTeamToCompare);
short compareNames(const TPlayer *pFirstPlayerToCompare, const TPlayer *pSecondPlayerToCompare);
short compareBirthdays(const TPlayer *pFirstPlayerToCompare, const TPlayer *pSecondPlayerToCompare);
short compareJerseyNumbers(const TPlayer *pFirstPlayerToCompare, const TPlayer *pSecondPlayerToCompare);
short compareNumberOfGoals(const TPlayer *pFirstPlayerToCompare, const TPlayer *pSecondPlayerToCompare);

void swapPlayers(TPlayer *pFirstPlayerToSwap, TPlayer *pSecondPlayerToSwap);

#endif // SORT_H_INCLUDED
