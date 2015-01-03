#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "tools.h"
#include "teams.h"
#include "datastructure.h"
#include "dateutils.h"
#include "sort.h"
#include "list.h"
#include "menu.h"
#include "search.h"


static void getName(char const *pNamePrompt, unsigned short maxLengthOfUserInput, unsigned short allowEmptyText, char **ppReturnString);

static short getListingDirection();
static void listOneTeam(const TTeam pTeamToPrint);
static void listOnePlayer(const TPlayer pPlayerToPrint);
static unsigned short selectTeam();

//globale Variablen (pfui!)

unsigned long globalTeamCounter = 0;
//TTeam globalTeams[MAXTEAMS];
TTeam *pFirstTeamInDVList = NULL, *pLastTeamInDVList = NULL;
THashElement aPlayerIndex[MAXINDEX];

extern void createTeam()
{
   TTeam *pTempTeam;
   pTempTeam = malloc(sizeof(TTeam));                                   // local Team to work with in this function
   unsigned short hashValue;

   char const *pTitle                = "Erfassung einer neuen Mannschaft";      // Arrays used for prompts
   char const *pNameOfTeamPrompt     = "Geben Sie bitte den Namen der Mannschaft ein:\n-> ";
   char const *pNameOfCoachPrompt    = "Geben Sie bitte den Namen des Trainers ein:\n-> ";

   printf("\n");
   printf("%s", pTitle);
   printf("\n");
   printLine('-', strlen(pTitle));
   printf("\n");

   // prompt of team name

   getName(pNameOfTeamPrompt, 50, 0, &(pTempTeam->nameOfTeam));

   // prompt of coach name

   getName(pNameOfCoachPrompt, 50, 0, &(pTempTeam->nameOfCoach) );

   // prompt of player adding

   pTempTeam->playerCount = 0;

   do
   {
      addPlayer(pTempTeam->players + pTempTeam->playerCount);

      hashValue = calcDivisionRemainder((pTempTeam->players + pTempTeam->playerCount)->nameOfPlayer);
      if(appendInEVList(aPlayerIndex + hashValue, pTempTeam, (pTempTeam->players + pTempTeam->playerCount), compareNames))
         printf("\n  Der Spieler %s wurde erfolgreich angelegt!\n\n", (pTempTeam->players + pTempTeam->playerCount)->nameOfPlayer);

      pTempTeam->playerCount++;

   } while( askPolarQuestion("Moechten Sie einen weiteren Spieler anlegen (j/n) ? ") );

   pTempTeam->numberOfMatchesWon     = 0;
   pTempTeam->numberOfMatchesTied    = 0;
   pTempTeam->numberOfMatchesLost    = 0;
   pTempTeam->numberOfGoalsScored    = 0;
   pTempTeam->numberOfGoalsLetIn     = 0;
   pTempTeam->numberOfPoints         = 0;


   if(insertInDVList(pTempTeam, compareTeams))
   {
      printf("\n  Die Mannschaft %s wurde erfolgreich mit ", pTempTeam->nameOfTeam);

      if(pTempTeam->playerCount > 1)
         printf("%hu Spielern ", pTempTeam->playerCount);
      else
         printf("einem Spieler ");

      printf("angelegt!\n");
   }

   waitForEnter();
}

extern void editTeam()
{
   printf("editTeam");
   waitForEnter();
}

extern void deleteTeam()
{
   char const *pTitle = "Loeschen einer Mannschaft";
   unsigned short input;
   unsigned short hashValue;
   unsigned short j;
   signed short i;

   TTeam *pCurrentTeamToDelete = pFirstTeamInDVList;


   printf("\n");
   printf("%s", pTitle);
   printf("\n");
   printLine('-', strlen(pTitle));

   input = selectTeam();

   //get pointeraddress of selected Team

   if(input == 0)
      return;

   else if(input == 1)
      pCurrentTeamToDelete = pFirstTeamInDVList;

   else
   {
      for(j = 2; j <= input; j++)
      {
         pCurrentTeamToDelete = pCurrentTeamToDelete->pNextTeamInDVList;
      }
   }

   for(i = (pCurrentTeamToDelete->playerCount) - 1; i >= 0; i--)
   {
      hashValue = calcDivisionRemainder((((pCurrentTeamToDelete)->players) + i)->nameOfPlayer);
      deleteFromEVList(aPlayerIndex + hashValue, pCurrentTeamToDelete->players + i);

      pCurrentTeamToDelete->playerCount--;

   }

   pCurrentTeamToDelete = removeFromDVList(pCurrentTeamToDelete, compareTeams);

   free(pCurrentTeamToDelete);

   waitForEnter();
}


extern void addPlayer(TPlayer * pPlayerToAdd)
{
   TPlayer TmpPlayer;                                                              // local Player to work with in this function

   char const *pTitle                   = "Erfassung der Spieler";                     // Arrays used for prompts
   char const *pNamePrompt              = "Geben Sie bitte den Namen des Spielers ein:\n-> ";
   char const *pBirthdayPrompt          = "Geben Sie bitte das Geburtsdatum des Spielers ein:\n-> ";
   char const *pJerseyNumberPrompt      = "Geben Sie bitte die Tricotnr. des Spielers ein:\n-> ";

//    unsigned short howCouldTextBeRead;


   //  print of title
   printf("\n");
   printf("%s", pTitle);
   printf("\n");
   printLine('-', strlen(pTitle));
//    printf("\n");


   // prompt of player name

   getName(pNamePrompt, 50, 0, &TmpPlayer.nameOfPlayer);

   // prompt of player birthday


   while(getDate(pBirthdayPrompt, &TmpPlayer.birthday) == 0)
   {
      printf("\nDas Datum konnte nicht interpretiert werden.\nBitte versuchen Sie es noch einmal.\n\n");
   }


   // prompt of jersey number

   while(getNumber(pJerseyNumberPrompt, &TmpPlayer.jerseyNumber, 1, 99) == 0)
   {
      printf("\nDas Datum konnte nicht interpretiert werden.\nBitte versuchen Sie es noch einmal.\n\n");
   }

   pPlayerToAdd->nameOfPlayer  = TmpPlayer.nameOfPlayer;
   pPlayerToAdd->birthday      = TmpPlayer.birthday;
   pPlayerToAdd->jerseyNumber  = TmpPlayer.jerseyNumber;
   pPlayerToAdd->numberOfGoals = 0;
}

static void getName(char const *pNamePrompt, unsigned short maxLengthOfUserInput, unsigned short allowEmptyText, char **ppReturnString)
{
   getText(pNamePrompt, maxLengthOfUserInput, allowEmptyText, ppReturnString);
}

extern void editPlayer()
{
   printf("editPlayer");
   waitForEnter();
}

extern void deletePlayer()
{
   printf("deletePlayer");
   waitForEnter();
}

extern void searchPlayer()
{
   //char const *pFirstTitle             = "Suchen";
   char const *pSecondTitle            = "Suchergebnis:";
/*   int selection;

   unsigned short const numMenuPoints = 4;
   char const * aMenuPoints[numMenuPoints];
   aMenuPoints[0] = "... nach Spielername";
   aMenuPoints[1] = "... nach Geburtsdatum";
   aMenuPoints[2] = "... nach Trikotnummer";
   aMenuPoints[3] = "... abbrechen";*/
   char const *pNamePrompt              = "Geben Sie bitte den Namen des gesuchten Spielers ein:\n-> ";
  /* char const *pBirthdayPrompt          = "Geben Sie bitte das Geburtsdatum des Spielers ein:\n-> ";
   char const *pJerseyNumberPrompt      = "Geben Sie bitte die Tricotnr. des Spielers ein:\n-> ";
*/
   TPlayer *pPlayerSearchedFor = calloc(1, sizeof(TPlayer));
   TListElement *pListElementPlayerFoundIn;
/*

   selection = getMenu(pFirstTitle, aMenuPoints, numMenuPoints);

   switch(selection)
   {
      case 1:
         getName(pNamePrompt, 50, 0, &(pPlayerSearchedFor->nameOfPlayer));
         pListElementPlayerFoundIn = searchForPlayer(aPlayerIndex, compareNames, pPlayerSearchedFor);
         break;

      case 2:
         while(getDate(pBirthdayPrompt, &(pPlayerSearchedFor->birthday)) == 0)
         {
            printf("\nDas Datum konnte nicht interpretiert werden.\nBitte versuchen Sie es noch einmal.\n\n");
         }
         pListElementPlayerFoundIn = searchForPlayer(aPlayerIndex, compareBirthdays, pPlayerSearchedFor);
         break;

      case 3:
         while(getNumber(pJerseyNumberPrompt, &(pPlayerSearchedFor->jerseyNumber), 1, 99) == 0)
         {
            printf("\nDas Datum konnte nicht interpretiert werden.\nBitte versuchen Sie es noch einmal.\n\n");
         }
         pListElementPlayerFoundIn = searchForPlayer(aPlayerIndex, compareJerseyNumbers, pPlayerSearchedFor);
         break;

      case 4:
         return;

      default:
         break;
   }


*/
   //pListElementPlayerFoundIn = searchForPlayer(aPlayerIndex, compareNames, pPlayerSearchedFor);

   getName(pNamePrompt, 50, 0, &(pPlayerSearchedFor->nameOfPlayer));
   pListElementPlayerFoundIn = searchForPlayer(aPlayerIndex, compareNames, pPlayerSearchedFor);

   printf("\n");
   printf("%s", pSecondTitle);
   printf("\n");
   printLine('-', strlen(pSecondTitle));
   printf("\n");

   if(pListElementPlayerFoundIn)
   {
      printf("In der Mannschaft %s\n   ",pListElementPlayerFoundIn->pTeam->nameOfTeam);
      listOnePlayer(*pListElementPlayerFoundIn->pPlayer);
      printf("\n");
   } else
   {
      printf("\nDer gesuchte Spieler konnte nicht gefunden werden.\n");
   }
   waitForEnter();
}

extern short sortTeams()
{
   int selection;
   char const * const title = "Sortieren";

   unsigned short const numMenuPoints = 5;
   char const * aMenuPoints[numMenuPoints];
   aMenuPoints[0] = "Spieler nach Namen sortieren";
   aMenuPoints[1] = "Spieler nach Geburtsdatum sortieren";
   aMenuPoints[2] = "Spieler nach Trickotnr. sortieren";
   aMenuPoints[3] = "Spieler nach Anzahl geschossener Tore sortieren";
   aMenuPoints[4] = "zureuck zum Hauptmenu";


   selection = getMenu(title, aMenuPoints, numMenuPoints);

   switch(selection)
   {
   case 1:
      quickSortPlayers(compareNames);
      return 1;
   case 2:
      quickSortPlayers(compareBirthdays);
      return 1;
   case 3:
      quickSortPlayers(compareJerseyNumbers);
      return 1;
   case 4:
      quickSortPlayers(compareNumberOfGoals);
      return 1;
   case 5:
      return 1;
   default:
      return 1;
   }

}

extern void listTeams()
{
   char const *pTitle = "Liste der Mannschaften";
   unsigned short wasAtLeastOneTeamPrinted = 0;

   TTeam *pCurrentTeamToList;

   short listingDirectionFromFirstElementToLast = getListingDirection();

   printf("\n%s\n", pTitle);
   printLine('-', strlen(pTitle));
   printf("\n");

   if(listingDirectionFromFirstElementToLast == 1)
   {
      for(pCurrentTeamToList = pFirstTeamInDVList; pCurrentTeamToList != NULL; pCurrentTeamToList = pCurrentTeamToList->pNextTeamInDVList)
      {
         listOneTeam(*pCurrentTeamToList);
         wasAtLeastOneTeamPrinted = 1;
      }
   } else if(listingDirectionFromFirstElementToLast == 0)
   {
      for(pCurrentTeamToList = pLastTeamInDVList; pCurrentTeamToList != NULL; pCurrentTeamToList = pCurrentTeamToList->pPreviousTeamInDVList)
      {
         listOneTeam(*pCurrentTeamToList);
         wasAtLeastOneTeamPrinted = 1;
      }
   } else
      return;


   if(pCurrentTeamToList == NULL && wasAtLeastOneTeamPrinted == 0)
      printf("-- Die Liste ist leer --\n");

   waitForEnter();
}

static short getListingDirection()
{
   unsigned short listingDirectionFromFirstElementToLast = 99;

   char const *pTitle = "Ausgabe";
   unsigned short const numMenuPoints = 3;
   char const * aMenuPoints[numMenuPoints];
   aMenuPoints[0] = "Aufwaerts ausgeben";
   aMenuPoints[1] = "Abwaerts ausgeben";
   aMenuPoints[2] = "zurueck zum Hauptmenu";


   listingDirectionFromFirstElementToLast = getMenu(pTitle, aMenuPoints, numMenuPoints);

   switch(listingDirectionFromFirstElementToLast)
   {
   case 1:
      return 1;
   case 2:
      return 0;
   case 3:
      return -1;
   default:
      break;
   }
   return 99;
}

static void listOneTeam(const TTeam pTeamToPrint)
{
   char const *pTeamNamePrompt         = "Name           : ";
   char const *pCoachNamePrompt        = "Trainer        : ";
   char const *pPlayerCountPrompt      = "Anzahl Spieler : ";
   char const *pListPlayerPrompt       = "Spieler: ";
   char const *pNumberOfMatchesWon     = "Siege          : ";
   char const *pNumberOfMatchesTied    = "Unentschieden  : ";
   char const *pNumberOfMatchesLost    = "Niederlagen    : ";
   char const *pGoalRatio              = "Torverhaeltnis : ";
   char const *pNumberOfPoints         = "Punkte:        : ";

   unsigned short i;


   printf("\n%s%s", pTeamNamePrompt, pTeamToPrint.nameOfTeam);
   printf("\n%s%s", pCoachNamePrompt, pTeamToPrint.nameOfCoach);
   printf("\n%s%u", pPlayerCountPrompt, pTeamToPrint.playerCount);

   printf("\n%s", pListPlayerPrompt);
   for(i = 0; i < pTeamToPrint.playerCount; i++)
   {
      printf("\n   %02u. ", i+1);
      listOnePlayer(pTeamToPrint.players[i]);
   }

   printf("\n");
   printf("\n%s%u", pNumberOfMatchesWon, pTeamToPrint.numberOfMatchesWon);
   printf("\n%s%u", pNumberOfMatchesTied, pTeamToPrint.numberOfMatchesTied);
   printf("\n%s%u", pNumberOfMatchesLost, pTeamToPrint.numberOfMatchesLost);
   printf("\n%s%u:%u", pGoalRatio, pTeamToPrint.numberOfGoalsScored, pTeamToPrint.numberOfGoalsLetIn);
   printf("\n%s%u", pNumberOfPoints, pTeamToPrint.numberOfPoints);
   printf("\n\n");

}

static void listOnePlayer(const TPlayer pPlayerToPrint)
{
   printf("%-25s (Trikotnummer: %2u;  ", pPlayerToPrint.nameOfPlayer, pPlayerToPrint.jerseyNumber);
   printf("* %02u.%02u.%04u;  ", pPlayerToPrint.birthday->day, pPlayerToPrint.birthday->month, pPlayerToPrint.birthday->year);
   printf("Tore: %2hu)", pPlayerToPrint.numberOfGoals);
}

extern void listIndex()
{
   unsigned short i;
   unsigned short hashValueUsedBefore;
   THashElement *pTempHashElement = aPlayerIndex + 0;
   TListElement *pTempListElement;

   clearScreen();

   for(i = 0; i <= MAXINDEX; pTempHashElement = aPlayerIndex + i)
   {

      if(pTempHashElement->pFirstListElement)
      {
         hashValueUsedBefore = 0;
         for(pTempListElement = pTempHashElement->pFirstListElement; pTempListElement != NULL; pTempListElement = pTempListElement->pNextListElement)
         {
            if(hashValueUsedBefore == 0)
               printf("Hashwert = %3hu:    Team = %-20s   Player = %s\n", i, pTempListElement->pTeam->nameOfTeam, pTempListElement->pPlayer->nameOfPlayer);
            else
               printf("                   Team = %-20s   Player = %s\n", pTempListElement->pTeam->nameOfTeam, pTempListElement->pPlayer->nameOfPlayer);

            hashValueUsedBefore = 1;
         }
      }
      i++;
      /*
      printf(" i = %hu \n", i);
      fflush(stdout);
      */
   }

   waitForEnter();
}

static unsigned short selectTeam()
{
   unsigned short i;
   int scanfRet = 0;
   unsigned short input;

   TTeam *pCurrentTeamToList;


   do
   {
      i = 0;

      printf("\n");

      if(pFirstTeamInDVList == 0)
      {
         printf("-- Es wurden noch keine Mannschaften geladen --\n");
         return 0;
      }


      for(pCurrentTeamToList = pFirstTeamInDVList; pCurrentTeamToList != NULL; pCurrentTeamToList = pCurrentTeamToList->pNextTeamInDVList)
      {
         i++;
         printf(" %hu: %s\n", i, pCurrentTeamToList->nameOfTeam);
      }

      printf("\nBitte waehlen Sie eine Mannschaft (0 zum Abbrechen) ?: ");
      scanfRet = scanf("%hu", &input);
      clearBuffer();

      if(input == 0)
         return 0;

   } while (scanfRet != 1 || input < 1 || input > i);

   return input;
}
