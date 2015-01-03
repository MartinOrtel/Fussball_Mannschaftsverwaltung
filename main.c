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
   char const * const title = "Fussball-Verwaltung Deluxe  Version 0.7.0";

   unsigned short const numMenuPoints = 9;
   char const * aMenuPoints[numMenuPoints];
   aMenuPoints[0] = "Neue Mannschaft anlegen";
   aMenuPoints[1] = "Spieler hinzufuegen";
   aMenuPoints[2] = "Spieler loeschen";
   aMenuPoints[3] = "Mannschaft loeschen";
   aMenuPoints[4] = "Suchen";
   aMenuPoints[5] = "Sortieren";
   aMenuPoints[6] = "Auflisten";
   aMenuPoints[7] = "Index auflisten";
   aMenuPoints[8] = "Programm beenden";

   loadTeams("teams.db");

   do
   {
      selection = getMenu(title, aMenuPoints, numMenuPoints);

      switch(selection)
      {
      case 1:
         createTeam();
         break;
      case 2: /* addPlayer(&globalTeams[globalTeamCounter].players[globalTeams[globalTeamCounter].playerCount]); */
         break;
      case 3:
         deletePlayer();
         break;
      case 4:
         deleteTeam();
         break;
      case 5:
         searchPlayer();
         break;
      case 6:
         sortTeams();
         break;
      case 7:
         listTeams();
         break;
      case 8:
         listIndex();
         break;
      case 9:
         if(terminateApplication() == 0)
            printf("Fehler beim Speichern!!");
         break;
      default:
         break;
      }

   }
   while(selection != 9);

   return 0;
}
