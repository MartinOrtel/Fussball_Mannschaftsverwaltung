#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "dateutils.h"
#include "menu.h"
#include "teams.h"
#include "database.h"

int main()
{
    int selection;
    char const * const title = "Fussball-Verwaltung Deluxe  Version 0.6.0";

    unsigned short const numMenuPoints = 8;
    char const * menuPoints[numMenuPoints];
    menuPoints[0] = "Neue Mannschaft anlegen";
    menuPoints[1] = "Spieler hinzufuegen";
    menuPoints[2] = "Spieler loeschen";
    menuPoints[3] = "Mannschaft loeschen";
    menuPoints[4] = "Suchen";
    menuPoints[5] = "Sortieren";
    menuPoints[6] = "Auflisten";
    menuPoints[7] = "Programm beenden";

    loadTeams("teams.db");

    do
    {
        selection = getMenu(title, menuPoints, numMenuPoints);

        switch(selection)
        {
            case 1: createTeam();                                       break;
            case 2: /* addPlayer(&globalTeams[globalTeamCounter].players[globalTeams[globalTeamCounter].playerCount]); */  break;
            case 3: deletePlayer();                                     break;
            case 4: deleteTeam();                                       break;
            case 5: searchPlayer();                                     break;
            case 6: sortTeams();                                        break;
            case 7: listTeams();                                        break;
            case 8: if(terminateApplication() == 0)
                        printf("Fehler beim Speichern!!");
                                                                        break;
            default:                                                   break;
        }

    } while(selection != 8);

    return 0;
}
