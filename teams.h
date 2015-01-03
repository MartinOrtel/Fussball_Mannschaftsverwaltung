#ifndef TEAMS_H_INCLUDED
#define TEAMS_H_INCLUDED
#include "datastructure.h"


extern void createTeam();

extern void editTeam();

extern void deleteTeam();

extern void addPlayer(TPlayer * pPlayersToAdd);

extern void editPlayer();

extern void deletePlayer();

extern void searchPlayer();

extern short sortTeams();

extern void listTeams();

extern void listIndex();

#endif // TEAMS_H_INCLUDED
