#include "sort.h"
#include "dateutils.h"
#include "datastructure.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

int DURCHLAUF = 1;

int partition(TPlayer *pPlayersToSort, const short ui, const short oi, short(*compare)(const TPlayer *, const TPlayer *))
{
   int i = ui + 1, j = oi;   // Laufindizes
   TPlayer temp;    // = *(pPlayersToSort + ui);
   TPlayer comp = *(pPlayersToSort + ui); //Vergleichselement (Schranke)

   while (i <= j)
   {
      // nächstes Element > comp von links suchen (im linken Teil)
      while (i <= j && compare(pPlayersToSort + i, &comp) <= 0)
         i++;

      // nächstes Element < comp von rechts suchen (im rechten Teil)
      while (i <= j && compare(pPlayersToSort + j, &comp) >= 0)
         j--;

      if (i < j)
      {
         temp = *(pPlayersToSort + i);
         *(pPlayersToSort + i) = *(pPlayersToSort + j);
         *(pPlayersToSort + j) = temp;
         //swapPlayers(pPlayersToSort + i, pPlayersToSort + j);
         i++;
         j--;
      }
   }

   i--;

   // setze Vergleichselement (Schranke) zwischen beide Teile
   temp = *(pPlayersToSort + i);
   *(pPlayersToSort + i) = *(pPlayersToSort + ui);
   *(pPlayersToSort + ui) = temp;
   //swapPlayers(pPlayersToSort + ui, pPlayersToSort + i);

   return(i);
}

void internQuickSortPlayers(TPlayer *pPlayersToSort, const short ui, const short oi, short(*compare)(const TPlayer *, const TPlayer *))   //short (*compare)(TAppointment const*, TAppointment const*), void (*swapApps)(TAppointment*, TAppointment*))
{
   // qsortCalendar(compare, swapApps, 0, AppointmentCount - 1);

    // Globale sortierungs-Variable setzen, damit listCalendar() weiß, wonach sortiert ist.
   int idx;   // Schranke einer Zerlegung

   if (ui >= oi)
      return;

   idx = partition(pPlayersToSort, ui, oi, compare);
   internQuickSortPlayers(pPlayersToSort, ui, idx - 1, compare); /* linken Teil rekursiv sortieren*/
   internQuickSortPlayers(pPlayersToSort, idx + 1, oi, compare); /* rechten Teil rekursiv sortieren*/

}

// Es gibt als Swap-Funktion nur eine einzige, diese wird hier eingesetzt.
void quickSortPlayers(short (*compare)(const TPlayer *, const TPlayer *))
{
    TTeam *pCurrentTeamToSort;

    for(pCurrentTeamToSort = pFirstTeamInDVList; pCurrentTeamToSort != NULL; pCurrentTeamToSort = pCurrentTeamToSort->pNextTeamInDVList)
    {
        internQuickSortPlayers(pCurrentTeamToSort->players, 0, (pCurrentTeamToSort->playerCount) - 1, compare);
    }

}


short compareTeams(const TTeam *pFirstTeamToCompare, const TTeam *pSecondTeamToCompare)
{
    return strcmp(pFirstTeamToCompare->nameOfTeam, pSecondTeamToCompare->nameOfTeam);
}

short compareNames(const TPlayer *pFirstPlayerToCompare, const TPlayer *pSecondPlayerToCompare)
{
    printf("Durchlauf Nummer %i Vergleiche %s mit %s\n", DURCHLAUF++, pFirstPlayerToCompare->nameOfPlayer, pSecondPlayerToCompare->nameOfPlayer);
    return strcmp(pFirstPlayerToCompare->nameOfPlayer, pSecondPlayerToCompare->nameOfPlayer);
}

short compareBirthdays(const TPlayer *pFirstPlayerToCompare, const TPlayer *pSecondPlayerToCompare)
{
    short diffMonths;
    short diffYears;


    diffYears = pFirstPlayerToCompare->birthday->year - pSecondPlayerToCompare->birthday->year;
    if (diffYears == 0)
    {
        diffMonths = pFirstPlayerToCompare->birthday->month - pSecondPlayerToCompare->birthday->month;
        if (diffMonths == 0)
            return pFirstPlayerToCompare->birthday->day - pSecondPlayerToCompare->birthday->day;
        else
            return diffMonths;
    }

    return diffYears;

}

short compareJerseyNumbers(const TPlayer *pFirstPlayerToCompare, const TPlayer *pSecondPlayerToCompare)
{
    return pFirstPlayerToCompare->jerseyNumber - pSecondPlayerToCompare->jerseyNumber;
}

short compareNumberOfGoals(const TPlayer *pFirstPlayerToCompare, const TPlayer *pSecondPlayerToCompare)
{
    return pFirstPlayerToCompare->numberOfGoals - pSecondPlayerToCompare->numberOfGoals;
}

void swapPlayers(TPlayer *pFirstPlayerToSwap, TPlayer *pSecondPlayerToSwap)
{
    TPlayer temp;

    temp = *pFirstPlayerToSwap;
    *pFirstPlayerToSwap = *pSecondPlayerToSwap;
    *pSecondPlayerToSwap = temp;
}
