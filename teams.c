#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "tools.h"
#include "teams.h"
#include "datastructure.h"
#include "dateutils.h"


static void listOneTeam(const TTeam pTeamToPrint);
static void listOnePlayer(const TPlayer pPlayerToPrint);

//globale Variablen (pfui!)

unsigned short globalTeamCounter = 0;
TTeam globalTeams[MAXTEAMS];

extern void createTeam()
{
    TTeam TmpTeam;                                                              // local Team to work with in this function

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

    getText( pNameOfTeamPrompt, 50, 0, &TmpTeam.nameOfTeam );

    // prompt of coach name

    getText(pNameOfCoachPrompt, 50, 0, &TmpTeam.nameOfCoach);

    // prompt of player adding

    TmpTeam.playerCount = 0;

    do
    {
        addPlayer(&TmpTeam.players[TmpTeam.playerCount]);

        TmpTeam.playerCount++;

       // i = askPolarQuestion("Moechten Sie einen weiteren Spieler eingeben (j/n)")

    } while( askPolarQuestion("Moechten Sie einen weiteren Spieler eingeben (j/n) ? ") );

    TmpTeam.numberOfMatchesWon  = 0;
    TmpTeam.numberOfMatchesTied = 0;
    TmpTeam.numberOfMatchesLost = 0;
    TmpTeam.numberOfGoalsScored = 0;
    TmpTeam.numberOfGoalsLetIn  = 0;
    TmpTeam.numberOfPoints      = 0;

    globalTeams[globalTeamCounter] = TmpTeam;
    globalTeamCounter++;

    waitForEnter();
}

extern void editTeam()
{
    printf("editTeam");
    waitForEnter();
}

extern void deleteTeam()
{
    printf("deleteTeam");
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

extern void sortTeams()
{
    printf("sortTeams");
    waitForEnter();
}

extern void listTeams()
{
    char const *pTitle                = "Liste der Mannschaften";

    unsigned short i;


    printf("\n%s\n", pTitle);
    printLine('-', strlen(pTitle));
    printf("\n");

    for(i = 0; i < globalTeamCounter; i++)
        listOneTeam(globalTeams[i]);

    if(globalTeamCounter == 0)
        printf("-- Die Liste ist leer --\n");

    waitForEnter();
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
    printf("%20s (%02u; ", pPlayerToPrint.nameOfPlayer, pPlayerToPrint.jerseyNumber);
    printf("* %02u.%02u.%04u)", pPlayerToPrint.birthday->day, pPlayerToPrint.birthday->month, pPlayerToPrint.birthday->year);
}
