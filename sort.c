#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "sort.h"
#include "dateutils.h"
#include "datastructure.h"

int DURCHLAUF = 1;

// todo Sortieren entfällt

// Globale Variable sortierung ist dafür da,
// damit listCalendar() weiß, wonach es die Ausgabe gruppieren soll.
// Default ist Sort_None - Keine Sortierung ausgewählt.
//Sortierung sortierung = Sort_None;

/*/**********************************************************/
/* Aus dem Skript geklaut und angepasst                   */
/* int partitionCalendar(int ui, int oi)                  */
/* Unterteilt das Calendar-Array in zwei Teile, wobei     */
/* im linken Teil alle Werte kleiner und im rechten Teil  */
/* alle Werte größer als die mittlere Schranke sind. Der  */
/* Index der Schranke wird zurückgegeben.                 */
/* Parameter: ui    - der untere Index des Teils des      */
/*                    Arrays, der sortiert werden soll    */
/*            oi    - der obere Index (entsprechend ui)   */
/* Rückgabe:  int   - Index der Schranke                  */
/*/**********************************************************/

int partition(TPlayer *pPlayersToSort, const short ui, const short oi, short(*compare)(const TPlayer *, const TPlayer *))
{
   int i = ui + 1, j = oi;   // Laufindizes
   TPlayer temp;    // = *(pPlayersToSort + ui);
   TPlayer comp = *(pPlayersToSort + ui); //Vergleichselement (Schranke)

   //printf("Aufruf: ui = %i; oi = %i; i = %i; j = %i\n", ui, oi, i, j);
   while (i <= j)
   {
      // nächstes Element > comp von links suchen (im linken Teil)
      while (i <= j && compare(pPlayersToSort + i, &comp) <= 0)
      {
         //printf("i = %i\n", i);
         i++;
      }

      // nächstes Element < comp von rechts suchen (im rechten Teil)
      while (i <= j && compare(pPlayersToSort + j, &comp) >= 0)
      {
         //printf("j = %i\n", j);
         j--;
      }

      if (i < j)
      {
         //printf("Tauschen: i = %i; j = %i\n", i, j);
         temp = *(pPlayersToSort + i);
         *(pPlayersToSort + i) = *(pPlayersToSort + j);
         *(pPlayersToSort + j) = temp;
         //swapPlayers(pPlayersToSort + i, pPlayersToSort + j);
         i++;
         j--;
      }
   }

   i--;

   //printf("Vergleichselement tauschen: i = %i; j = %i\n", i, j);

   // setze Vergleichselement (Schranke) zwischen beide Teile
   temp = *(pPlayersToSort + i);
   *(pPlayersToSort + i) = *(pPlayersToSort + ui);
   *(pPlayersToSort + ui) = temp;
   //swapPlayers(pPlayersToSort + ui, pPlayersToSort + i);

   return(i);
}

/**********************************************************/
/* void qsortCalendar(, int ui, int oi)                   */
/* Unterteilt das Calendar-Array in zwei Teile (Funktion  */
/* partition) und ruft sich selber für beide Teile        */
/* erneut auf.                                            */
/* Parameter: ui    - der untere Index des Teils des      */
/*                    Arrays, der sortiert werden soll    */
/*            oi    - der obere Index (entsprechend ui)   */
/* Rückgabe:  keine                                       */
//**********************************************************/
/*static void qsortCalendar(short (*compare)(TAppointment const*, TAppointment const*), void (*swapApps)(TAppointment*, TAppointment*), int ui, int oi)
{
   int idx;   // Schranke einer Zerlegung

   if (ui >= oi)
      return;
   else
   {
      idx = partitionCalendar(compare, swapApps, ui, oi);
      qsortCalendar(compare, swapApps, ui, idx - 1); // linken Teil rekursiv sortieren
      qsortCalendar(compare, swapApps, idx + 1, oi); // rechten Teil rekursiv sortieren
   }
}
*/
/***********************************************************/
/* Quick-Sort aus dem Skript geklaut und angepasst.        */
/* Sortiert das angegebene Zahlen-Array in aufsteigender   */
/* Reihenfolge.                                            */
/* Parameter: Array  - Zeiger auf das zu sortierende Array */
/*            Anzahl - Anzahl der Elemente im Array        */
/* Rückgabe:  keine                                        */
//***********************************************************/
/*static void _quickSortCalendar(short (*compare)(TAppointment const*, TAppointment const*), void (*swapApps)(TAppointment*, TAppointment*))
{
    qsortCalendar(compare, swapApps, 0, AppointmentCount - 1);

    // Globale sortierungs-Variable setzen, damit listCalendar() weiß, wonach sortiert ist.
    if (compare == cmpApps_DateTime)
        sortierung = Sort_DateTime;
    else if (compare == cmpApps_DescDateTime)
        sortierung = Sort_DescDateTime;
    else if (compare == cmpApps_DurDateTime)
        sortierung = Sort_DurDateTime;
    else if (compare == cmpApps_LocDateTime)
        sortierung = Sort_LocDateTime;
    else
        assert(0);
}

// Es gibt als Swap-Funktion nur eine einzige, diese wird hier eingesetzt.
void quickSortCalendar(short (*compare)(TAppointment const*, TAppointment const*))
{
    _quickSortCalendar(compare, swapAppointments);
}
*/

void quickSortPlayers(TPlayer *pPlayersToSort, const short ui, const short oi, short(*compare)(const TPlayer *, const TPlayer *))   //short (*compare)(TAppointment const*, TAppointment const*), void (*swapApps)(TAppointment*, TAppointment*))
{
   // qsortCalendar(compare, swapApps, 0, AppointmentCount - 1);

    // Globale sortierungs-Variable setzen, damit listCalendar() weiß, wonach sortiert ist.
   int idx;   // Schranke einer Zerlegung

   if (ui >= oi)
      return;

   idx = partition(pPlayersToSort, ui, oi, compare);
   quickSortPlayers(pPlayersToSort, ui, idx - 1, compare); /* linken Teil rekursiv sortieren*/
   quickSortPlayers(pPlayersToSort, idx + 1, oi, compare); /* rechten Teil rekursiv sortieren*/

}

// Es gibt als Swap-Funktion nur eine einzige, diese wird hier eingesetzt.
void externQuickSortPlayers(short (*compare)(const TPlayer *, const TPlayer *))
{
    unsigned short i;

    for(i = 0; i < globalTeamCounter; i++)
    {
        printf("sortiere %s (%hu Spieler) ... ", globalTeams[i].nameOfTeam, globalTeams[i].playerCount);
        fflush(stdout);
        quickSortPlayers(globalTeams[i].players, 0, ((globalTeams[i].playerCount) - 1), compare);
        printf("ok\n");
    }
}



short compareNames(const TPlayer *pFirstPlayerToCompare, const TPlayer *pSecondPlayerToCompare)
{
    //printf("Durchlauf Nummer %i Vergleiche %s mit %s\n", DURCHLAUF++, pFirstPlayerToCompare->nameOfPlayer, pSecondPlayerToCompare->nameOfPlayer);
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
    //printf("Durchlauf Nummer %i Vergleiche %hu mit %hu\n", DURCHLAUF++, pFirstPlayerToCompare->numberOfGoals, pSecondPlayerToCompare->numberOfGoals);
    return pFirstPlayerToCompare->numberOfGoals - pSecondPlayerToCompare->numberOfGoals;
}

void swapPlayers(TPlayer *pFirstPlayerToSwap, TPlayer *pSecondPlayerToSwap)
{
    TPlayer temp;

    temp = *pFirstPlayerToSwap;
    *pFirstPlayerToSwap = *pSecondPlayerToSwap;
    *pSecondPlayerToSwap = temp;
}
