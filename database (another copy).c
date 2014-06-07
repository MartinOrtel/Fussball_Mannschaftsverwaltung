#include <stdio.h>
#include <string.h>

#include "teams.h"
#include "database.h"
#include "dateutils.h"



static short saveOneTeam(FILE *const pFileHandleDataBase, const TTeam pTeamToSave);
static short savePlayers(FILE *const pFileHandleDataBase, const TPlayer * pPlayersToSave, const unsigned short playerCount);
static short saveOnePlayer(FILE *const pFileHandleDataBase, const TPlayer playerToSave);
static short loadOneTeam(FILE *const pFileHandleDataBase, FILE *const pFileHandleErrorLog, TTeam * pTeamToLoad);
static short loadOneTeamAttribute(FILE *const pFileHandleDataBase, FILE *const pFileHandleErrorLog, const char * pReadStringFromFile, TTeam * pTeamToLoad);
static short loadOnePlayer(FILE *const pFileHandleDataBase, FILE *const pFileHandleErrorLog, TPlayer * pPlayersToLoad);
static short loadOnePlayerAttribute(FILE *const pFileHandleDataBase, FILE *const pFileHandleErrorLog, const char * pReadStringFromFile, TPlayer* pPlayerToLoad);

// saving

extern short saveTeams(char const * pFileNameOfFileToSave)
{
    unsigned short i;

    FILE *pFileHandleDataBase;


    pFileHandleDataBase = fopen(pFileNameOfFileToSave, "wt");

    if(pFileHandleDataBase != NULL)
    {
        if(fprintf(pFileHandleDataBase, "<Daten>\n"))
        {
            for(i = 0; i < globalTeamCounter; i++)
                if(saveOneTeam(pFileHandleDataBase, globalTeams[i]) == 0)
                {
                    fclose(pFileHandleDataBase);
                    remove(pFileNameOfFileToSave);
                    return 0;
                }
        }else
        {
            fclose(pFileHandleDataBase);
            remove(pFileNameOfFileToSave);
            return 0;
        }

        if(fprintf(pFileHandleDataBase, "</Daten>") == 0)
        {
            return 0;
            fclose(pFileHandleDataBase);
            remove(pFileNameOfFileToSave);
        }
    }

    fclose(pFileHandleDataBase);

    return 1;
}

static short saveOneTeam(FILE *const pFileHandleDataBase, const TTeam pTeamToSave)
{
//    char tmpString[100];

//    assert(pTeamToSave);

    if(fprintf(pFileHandleDataBase, " <Team>\n"))
    {
        if(fprintf(pFileHandleDataBase, "  <Name>%s</Name>\n", pTeamToSave.nameOfTeam) == 0)
            return 0;
        if(fprintf(pFileHandleDataBase, "  <Trainer>%s</Trainer>\n", pTeamToSave.nameOfCoach) == 0)
            return 0;
        if(savePlayers(pFileHandleDataBase, pTeamToSave.players, pTeamToSave.playerCount) == 0)
            return 0;
        if(fprintf(pFileHandleDataBase, "  <Win>%hu</Win>\n", pTeamToSave.numberOfMatchesWon) == 0)
            return 0;
        if(fprintf(pFileHandleDataBase, "  <Tie>%hu</Tie>\n", pTeamToSave.numberOfMatchesTied) == 0)
            return 0;
        if(fprintf(pFileHandleDataBase, "  <Defeat>%hu</Defeat>\n", pTeamToSave.numberOfMatchesLost) == 0)
            return 0;
        if(fprintf(pFileHandleDataBase, "  <Goals>%hu</Goals>\n", pTeamToSave.numberOfGoalsScored) == 0)
            return 0;
        if(fprintf(pFileHandleDataBase, "  <GuestGoals>%hu</GuestGoals>\n", pTeamToSave.numberOfGoalsLetIn) == 0)
            return 0;
        if(fprintf(pFileHandleDataBase, "  <Points>%hu</Points>\n", pTeamToSave.numberOfPoints) == 0)
            return 0;

    } else
    {
        return 0;
    }

    if(fprintf(pFileHandleDataBase, " </Team>\n") == 0)
        return 0;

    return 1;
}

static short savePlayers(FILE *const pFileHandleDataBase, const TPlayer * pPlayersToSave, const unsigned short playerCount)
{
    unsigned short i;

    for(i = 0; i < playerCount; i++)
            if(saveOnePlayer(pFileHandleDataBase, pPlayersToSave[i]) == 0)
                return 0;

    return 1;
}

static short saveOnePlayer(FILE *const pFileHandleDataBase, const TPlayer playerToSave)
{

    if(fprintf(pFileHandleDataBase, "  <Player>\n") == 0)
        return 0;
    if(fprintf(pFileHandleDataBase, "   <Name>%s</Name>\n", playerToSave.nameOfPlayer) == 0)
        return 0;
    if(fprintf(pFileHandleDataBase, "   <Birthday>%02u.%02u.%hu</Birthday>\n", playerToSave.birthday->day, playerToSave.birthday->month, playerToSave.birthday->year) == 0)
        return 0;
    if(fprintf(pFileHandleDataBase, "   <TricotNr>%hu</TricotNr>\n", playerToSave.jerseyNumber) == 0)
        return 0;
    if(fprintf(pFileHandleDataBase, "   <Goals>%hu</Goals>\n", playerToSave.numberOfGoals) == 0)
        return 0;
    if(fprintf(pFileHandleDataBase, "  </Player>\n") == 0)
        return 0;

    return 1;
}


// loading

extern short loadTeams(char const * pFileNameOfFileToLoad)
{
    TTeam tempTeam;

    const char const *pFileNameOfErrorLog = "error.log";

    FILE *pFileHandleErrorLog;
    FILE *pFileHandleDataBase;

    char readBuffer[100];



    pFileHandleErrorLog = fopen(pFileNameOfErrorLog, "awt");
    pFileHandleDataBase = fopen(pFileNameOfFileToLoad, "rt");


    if(pFileHandleDataBase)
    {
        if(pFileHandleErrorLog)
        {
            if(fgets(readBuffer, sizeof(readBuffer), pFileHandleDataBase)/* == NULL      !!!ERRORHANDLING NOCH IMPLEMENTIEREN!!!   */)
            {
                if(strncmp(readBuffer, STARTTAG_START, sizeof(STARTTAG_START) - 1) == 0)
                {
                    if(fgets(readBuffer, sizeof(readBuffer), pFileHandleDataBase)/* == NULL      !!!ERRORHANDLING NOCH IMPLEMENTIEREN!!!   */)
                    {
                        if(strncmp(readBuffer, STARTTAG_TEAM, sizeof(STARTTAG_TEAM) - 1) == 0)
                        {
                            loadOneTeam(pFileHandleDataBase, pFileHandleErrorLog, &(tempTeam));
                        }
                    } else
                    {
                        if (fputs("errormessage!!", pFileHandleErrorLog) == EOF)
                        {
                            puts("ALLES KAPUTT!!!");
                            fclose(pFileHandleDataBase);
                            fclose(pFileHandleErrorLog);
                            return 0;
                        }
                    }
                }
            } else
            {
                if (fputs("errormessage!!", pFileHandleErrorLog) == EOF)
                {
                    puts("ALLES KAPUTT!!!");
                    fclose(pFileHandleDataBase);
                    fclose(pFileHandleErrorLog);
                    return 0;
                }
            }
        }
    }

    globalTeams[globalTeamCounter] = tempTeam;

    return 1;
}

extern short loadOneTeam(FILE *const pFileHandleDataBase, FILE *const pFileHandleErrorLog, TTeam * pTeamToLoad)
{
    char readBuffer[100];

    pTeamToLoad->playerCount = 0;

    do
    {
        if(fgets(readBuffer, sizeof(readBuffer), pFileHandleDataBase))
        {
            if(loadOneTeamAttribute(pFileHandleDataBase, pFileHandleErrorLog, readBuffer, pTeamToLoad) == 0)
            {
                if (fputs("errormessage!!", pFileHandleErrorLog) == EOF)
                    puts("ALLES KAPUTT!!!");

            }
        } else
        {
            if (fputs("errormessage!!", pFileHandleErrorLog) == EOF)
            {
                puts("ALLES KAPUTT!!!");
                return 0;
            }
        }
    } while(strncmp(readBuffer, ENDTAG_TEAM, sizeof(ENDTAG_TEAM) - 1) != 0);

    globalTeamCounter++;

    return 1;
}

static short loadOneTeamAttribute(FILE *const pFileHandleDataBase, FILE *const pFileHandleErrorLog, const char * pReadStringFromFile, TTeam * pTeamToLoad)
{
    char scanfFormatAsString[100];
    char readBuffer[100];


    if(strncmp(pReadStringFromFile, STARTTAG_TEAM_NAME, sizeof(STARTTAG_TEAM_NAME) - 1) == 0)
    {
        sprintf(scanfFormatAsString, "%s%s%s", STARTTAG_TEAM_NAME, "%s", ENDTAG_TEAM_NAME);

        if(sscanf(pReadStringFromFile, scanfFormatAsString, &(pTeamToLoad->nameOfTeam)) == 1)
            return 1;

        return 0;

    } else if(strncmp(pReadStringFromFile, STARTTAG_TEAM_COACH, sizeof(STARTTAG_TEAM_COACH) - 1) == 0)
    {
        sprintf(scanfFormatAsString, "%s%s%s", STARTTAG_TEAM_COACH, "%s", ENDTAG_TEAM_COACH);

        if(sscanf(pReadStringFromFile, scanfFormatAsString, &(pTeamToLoad->nameOfCoach)) == 1)
            return 1;

        return 0;

    } else if(strncmp(pReadStringFromFile, STARTTAG_TEAM_PLAYER, sizeof(STARTTAG_TEAM_PLAYER) - 1) == 0)
    {
        if(loadOnePlayer(pFileHandleDataBase, pFileHandleErrorLog, &(pTeamToLoad->players[pTeamToLoad->playerCount])))
        {
            pTeamToLoad->playerCount++;
            return 1;
        }

    } else if(strncmp(pReadStringFromFile, STARTTAG_TEAM_MATCHESWON, sizeof(STARTTAG_TEAM_MATCHESWON) - 1) == 0)
    {
        return 1;
    } else if(strncmp(pReadStringFromFile, STARTTAG_TEAM_MATCHESTIED, sizeof(STARTTAG_TEAM_MATCHESTIED) - 1) == 0)
    {
        return 1;
    } else if(strncmp(pReadStringFromFile, STARTTAG_TEAM_MATCHESLOST, sizeof(STARTTAG_TEAM_MATCHESLOST) - 1) == 0)
    {
        return 1;
    } else if(strncmp(pReadStringFromFile, STARTTAG_TEAM_GOALS, sizeof(STARTTAG_TEAM_GOALS) - 1) == 0)
    {
        return 1;
    } else if(strncmp(pReadStringFromFile, STARTTAG_TEAM_GOALSLETIN, sizeof(STARTTAG_TEAM_GOALSLETIN) - 1) == 0)
    {
        return 1;
    } else if(strncmp(pReadStringFromFile, STARTTAG_TEAM_POINTS, sizeof(STARTTAG_TEAM_POINTS) - 1) == 0)
    {
        return 1;
    }

    return 0;
}

static short loadOnePlayer(FILE *const pFileHandleDataBase, FILE *const pFileHandleErrorLog, TPlayer * pPlayersToLoad)
{
    char readBuffer[100];

    unsigned short i = 0;


    if(fgets(readBuffer, sizeof(readBuffer), pFileHandleDataBase) == NULL)
    {
        if (fputs("errormessage!!", pFileHandleErrorLog) == EOF)
            puts("ALLES KAPUTT!!!");

        return 0;
    }

    while(strncmp(readBuffer, ENDTAG_TEAM_PLAYER, sizeof(ENDTAG_TEAM_PLAYER) - 1) != 0)
    {
        if(loadOnePlayerAttribute(pFileHandleDataBase, pFileHandleErrorLog, readBuffer, &pPlayersToLoad[i]) == 0)
        {
            if (fputs("errormessage!!", pFileHandleErrorLog) == EOF)
                puts("ALLES KAPUTT!!!");
        }

        if(fgets(readBuffer, sizeof(readBuffer), pFileHandleDataBase) == NULL)
        {
            if (fputs("errormessage!!", pFileHandleErrorLog) == EOF)
                puts("ALLES KAPUTT!!!");

            return 0;
        }
    }


    return 1;
}

static short loadOnePlayerAttribute(FILE *const pFileHandleDataBase, FILE *const pFileHandleErrorLog, const char * pReadStringFromFile, TPlayer* pPlayerToLoad)
{
    char scanfFormatAsString[100];
    char readBuffer[100];


    if(strncmp(pReadStringFromFile, STARTTAG_TEAM_PLAYER_NAME, sizeof(STARTTAG_TEAM_PLAYER_NAME) - 1) == 0)
    {
        sprintf(scanfFormatAsString, "%s%s%s", STARTTAG_TEAM_PLAYER_NAME, "%s", ENDTAG_TEAM_PLAYER_NAME);

        if(sscanf(pReadStringFromFile, scanfFormatAsString, &(pPlayerToLoad->nameOfPlayer)) == EOF)
            return 0;

        return 1;

    } else if(strncmp(pReadStringFromFile, STARTTAG_TEAM_PLAYER_BIRTHDAY, sizeof(STARTTAG_TEAM_PLAYER_BIRTHDAY) - 1) == 0)
    {
        sprintf(scanfFormatAsString, "%s%s%s", STARTTAG_TEAM_PLAYER_BIRTHDAY, "%s", ENDTAG_TEAM_PLAYER_BIRTHDAY);

        if(sscanf(pReadStringFromFile, scanfFormatAsString, readBuffer))
            if(getDateFromString(readBuffer, pPlayerToLoad->birthday))
                return 1;

    } else if(strncmp(pReadStringFromFile, STARTTAG_TEAM_PLAYER_JERSEYNUMBER, sizeof(STARTTAG_TEAM_PLAYER_JERSEYNUMBER) - 1) == 0)
    {
        sprintf(scanfFormatAsString, "%s%s%s", STARTTAG_TEAM_PLAYER_JERSEYNUMBER, "%hu", ENDTAG_TEAM_PLAYER_JERSEYNUMBER);

        if(sscanf(pReadStringFromFile, scanfFormatAsString, &(pPlayerToLoad->jerseyNumber)) == EOF)
            return 0;

        return 1;

    } else if(strncmp(pReadStringFromFile, STARTTAG_TEAM_PLAYER_GOALS, sizeof(STARTTAG_TEAM_PLAYER_GOALS) - 1) == 0)
    {
        sprintf(scanfFormatAsString, "%s%s%s", STARTTAG_TEAM_PLAYER_GOALS, "%hu", ENDTAG_TEAM_PLAYER_GOALS);

        if(sscanf(pReadStringFromFile, scanfFormatAsString, &(pPlayerToLoad->numberOfGoals)) == EOF)
            return 0;

        return 1;
    }

    return 0;
}
