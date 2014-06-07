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

extern void sortTeams();

extern void listTeams();

//static void listOneTeam(const TTeam pTeamToPrint);

//static void listOnePlayer();

#endif // TEAMS_H_INCLUDED
