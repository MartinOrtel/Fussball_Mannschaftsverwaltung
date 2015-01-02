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

static short getListingDirection();
static void listOneTeam(const TTeam pTeamToPrint);
static void listOnePlayer(const TPlayer pPlayerToPrint);

//globale Variablen (pfui!)

unsigned long globalTeamCounter = 0;
//TTeam globalTeams[MAXTEAMS];
TTeam *pFirstTeamInDVList = NULL, *pLastTeamInDVList = NULL;

extern void createTeam()
{
    TTeam *pTempTeam;
    pTempTeam = malloc(sizeof(TTeam));                                   // local Team to work with in this function

    char const *pTitle                = "Erfassung einer neuen Mannschaft";      // Arrays used for prompts
    char const *pNameOfTeamPrompt     = "Geben Sie bitte den Namen der Mannschaft ein:\n-> ";
    char const *pNameOfCoachPrompt    = "Geben Sie bitte den Namen des Trainers ein:\n-> ";
//    char const *pDatePrompt           = "Datum         :";
//    char const *pTimePrompt           = "Uhrzeit       :";
//    char const *pDescriptionPrompt    = "Beschreibung  :";
//    char const *pLocationPrompt       = "Ort           :";
//    char const *pDurationPrompt       = "Dauer         :";

//    unsigned short howCouldTextBeRead;

    //  print of title
    printf("\n");
    printf("%s", pTitle);
    printf("\n");
    printLine('-', strlen(pTitle));
    printf("\n");

    // prompt of team name

    getText( pNameOfTeamPrompt, 50, 0, &(pTempTeam->nameOfTeam) );

    // prompt of coach name

    getText(pNameOfCoachPrompt, 50, 0, &(pTempTeam->nameOfCoach) );

    // prompt of player adding

    pTempTeam->playerCount = 0;

    do
    {
        addPlayer(&(pTempTeam->players[pTempTeam->playerCount]));

        pTempTeam->playerCount++;

       // i = askPolarQuestion("Moechten Sie einen weiteren Spieler eingeben (j/n)")

    } while( askPolarQuestion("Moechten Sie einen weiteren Spieler eingeben (j/n) ? ") );

    pTempTeam->numberOfMatchesWon     = 0;
    pTempTeam->numberOfMatchesTied    = 0;
    pTempTeam->numberOfMatchesLost    = 0;
    pTempTeam->numberOfGoalsScored    = 0;
    pTempTeam->numberOfGoalsLetIn     = 0;
    pTempTeam->numberOfPoints         = 0;
   // pTempTeam->pNextTeamInDVList      = NULL;
   // pTempTeam->pPreviousTeamInDVList  = NULL;

//    globalTeams[globalTeamCounter] = tempTeam;
//    globalTeamCounter++;

    insertInDVList(pTempTeam, compareTeams);


    waitForEnter();
}

extern void editTeam()
{
    printf("editTeam");
    waitForEnter();
}

extern void deleteTeam()
{
    char const *pTitle = "Liste der Mannschaften";
    unsigned short i;
    unsigned short wasAtLeastOneTeamPrinted = 0;
    int scanfRet = 0;
    unsigned short input;
    unsigned short j;

    TTeam *pCurrentTeamToList, *pCurrentTeamToDelete;

    do
    {
        clearScreen();
        printf("\n%s\n", pTitle);
        printLine('-', strlen(pTitle));
        printf("\n");

        i = 0;

        for(pCurrentTeamToList = pFirstTeamInDVList; pCurrentTeamToList != NULL; pCurrentTeamToList = pCurrentTeamToList->pNextTeamInDVList)
        {
            i++;
            printf(" %hu: %s\n", i, pCurrentTeamToList->nameOfTeam);
            wasAtLeastOneTeamPrinted = 1;
        }

        if(pCurrentTeamToList == NULL && wasAtLeastOneTeamPrinted == 0)
        {
            printf("-- Die Liste ist leer --\n");
            waitForEnter();
            return;
        }

        printf("\nWelche Mannschaft moechten Sie loeschen (0 fuer Abbrechen) ?: ");
        scanfRet = scanf("%hu", &input);
        clearBuffer();

        if(input == 0)
            return;

    } while (scanfRet != 1 || input < 1 || input > i);

    //get pointeraddress of selected Team

    if(input == 1)
        pCurrentTeamToDelete = pFirstTeamInDVList;
    else
    {
        for(j = 2; j <= input; j++)
        {
            pCurrentTeamToDelete = pFirstTeamInDVList->pNextTeamInDVList;
        }
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

    getText(pNamePrompt, 50, 0, &TmpPlayer.nameOfPlayer);

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
    pPlayerToAdd->numberOfGoals     = 0;

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
    printf("searchPlayer");
    waitForEnter();
}

extern short sortTeams()
{
   // int i = 0;
    int selection;
    char const * const title = "Sortieren";

    unsigned short const numMenuPoints = 5;
    char const * menuPoints[numMenuPoints];
    menuPoints[0] = "Spieler nach Namen sortieren";
    menuPoints[1] = "Spieler nach Geburtsdatum sortieren";
    menuPoints[2] = "Spieler nach Trickotnr. sortieren";
    menuPoints[3] = "Spieler nach Anzahl geschossener Tore sortieren";
    menuPoints[4] = "zureuck zum Hauptmenu";


 //   do
 //   {
        selection = getMenu(title, menuPoints, numMenuPoints);

        switch(selection)
        {
            case 1: quickSortPlayers(compareNames);            return 1;
            case 2: quickSortPlayers(compareBirthdays);        return 1;
            case 3: quickSortPlayers(compareJerseyNumbers);    return 1;
            case 4: quickSortPlayers(compareNumberOfGoals);    return 1;
            case 5:                                                  return 1;
            default:                                                 return 1;
        }
//    } while()
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
    char const * menuPoints[numMenuPoints];
    menuPoints[0] = "Aufwaerts ausgeben";
    menuPoints[1] = "Abwaerts ausgeben";
    menuPoints[2] = "zurueck zum Hauptmenu";


    listingDirectionFromFirstElementToLast = getMenu(pTitle, menuPoints, numMenuPoints);

    switch(listingDirectionFromFirstElementToLast)
    {
        case 1:     return 1;
        case 2:     return 0;
        case 3:     return -1;
        default:    break;
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
    printf("%-25s (%02u; ", pPlayerToPrint.nameOfPlayer, pPlayerToPrint.jerseyNumber);
    printf("* %02u.%02u.%04u; ", pPlayerToPrint.birthday->day, pPlayerToPrint.birthday->month, pPlayerToPrint.birthday->year);
    printf("%2hu)", pPlayerToPrint.numberOfGoals);
}
