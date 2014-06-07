#include <stdio.h>
#include <string.h>

#include "teams.h"
#include "database.h"



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
        if(fprintf(pFileHandleDataBase, "  <Win>%u</Win>\n", pTeamToSave.numberOfMatchesWon) == 0)
            return 0;
        if(fprintf(pFileHandleDataBase, "  <Tie>%u</Tie>\n", pTeamToSave.numberOfMatchesTied) == 0)
            return 0;
        if(fprintf(pFileHandleDataBase, "  <Defeat>%u</Defeat>\n", pTeamToSave.numberOfMatchesLost) == 0)
            return 0;
        if(fprintf(pFileHandleDataBase, "  <Goals>%u</Goals>\n", pTeamToSave.numberOfGoalsScored) == 0)
            return 0;
        if(fprintf(pFileHandleDataBase, "  <GuestGoals>%u</GuestGoals>\n", pTeamToSave.numberOfGoalsLetIn) == 0)
            return 0;
        if(fprintf(pFileHandleDataBase, "  <Points>%u</Points>\n", pTeamToSave.numberOfPoints) == 0)
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
    if(fprintf(pFileHandleDataBase, "   <Birthday>%02u.%02u.%u</Birthday>\n", playerToSave.birthday->day, playerToSave.birthday->month, playerToSave.birthday->year) == 0)
        return 0;
    if(fprintf(pFileHandleDataBase, "   <TricotNr>%u</TricotNr>\n", playerToSave.jerseyNumber) == 0)
        return 0;
    if(fprintf(pFileHandleDataBase, "   <Goals>%u</Goals>\n", playerToSave.numberOfGoals) == 0)
        return 0;
    if(fprintf(pFileHandleDataBase, "  </Player>\n") == 0)
        return 0;

    return 1;
}


// loading

extern short loadTeams(char const * pFileNameOfFileToLoad)
{
    TTeam pTeamToLoad;

    const char const *pFileNameOfErrorLog = "error.log";

    FILE *pFileHandleErrorLog;
    FILE *pFileHandleDataBase;

    char readBuffer[100];

//    int i = 0;


    pFileHandleErrorLog = fopen(pFileNameOfErrorLog, "awt");
    pFileHandleDataBase = fopen(pFileNameOfFileToLoad, "rt");


    if(pFileHandleDataBase)
    {
        if(pFileHandleErrorLog)
        {
            if(fgets(readBuffer, sizeof(readBuffer), pFileHandleDataBase)/* == NULL      !!!ERRORHANDLING NOCH IMPLEMENTIEREN!!!   */)
            {
                if(strcmp(readBuffer, "<Daten>\n") == 0)
                {
                    if(fgets(readBuffer, sizeof(readBuffer), pFileHandleDataBase)/* == NULL      !!!ERRORHANDLING NOCH IMPLEMENTIEREN!!!   */)
                    {
                        if(strcmp(readBuffer, " <Team>\n") == 0)
                        {
                            loadOneTeam(pFileHandleDataBase, pFileHandleErrorLog, &pTeamToLoad);
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


/*

        if((i = feof(pFileHandleDataBase)))
        {
            fclose(pFileHandleDataBase);
            return 0;
        }
        if((i = ferror(pFileHandleDataBase)))
        {
            fclose(pFileHandleDataBase);
            return 0;
        }


        fscanf(pFileHandleDataBase, " < Tum >");
        if((i = feof(pFileHandleDataBase)))
        {
            fclose(pFileHandleDataBase);
            return 0;
        }
        if((i = ferror(pFileHandleDataBase)))
        {
            fclose(pFileHandleDataBase);
            return 0;
        }
*/
    }

    return 1;
}

extern short loadOneTeam(FILE *const pFileHandleDataBase, FILE *const pFileHandleErrorLog, TTeam * pTeamToLoad)
{
    const char * pDataBaseEndTagForTeam = " </Team>\n";

    char readBuffer[100];

    do
    {
        if(fgets(readBuffer, sizeof(readBuffer), pFileHandleDataBase)/* == NULL      !!!ERRORHANDLING NOCH IMPLEMENTIEREN!!!   */)
        {
            //if(strncmp(readBuffer, pDataBaseEndTagForTeam, sizeof(pDataBaseEndTagForTeam)) != 0)
            //{
                //if(fgets(readBuffer, sizeof(readBuffer), pFileHandleDataBase)/* == NULL      !!!ERRORHANDLING NOCH IMPLEMENTIEREN!!!   */)
                //{
                    if(loadOneTeamAttribute(pFileHandleDataBase, pFileHandleErrorLog, readBuffer, pTeamToLoad) == 0)
                    {
                        if (fputs("errormessage!!", pFileHandleErrorLog) == EOF)
                            puts("ALLES KAPUTT!!!");

                        //return 0;
                    }
                //} else
                //{
                //    if (fputs("errormessage!!", pFileHandleErrorLog) == EOF)
                //    {
                //        puts("ALLES KAPUTT!!!");
                //        return 0;
                //    }
                //}
            //}
        } else
        {
            if (fputs("errormessage!!", pFileHandleErrorLog) == EOF)
            {
                puts("ALLES KAPUTT!!!");
                return 0;
            }
        }
    } while(strncmp(readBuffer, pDataBaseEndTagForTeam, sizeof(pDataBaseEndTagForTeam)) != 0);


    return 1;
}

static short loadOneTeamAttribute(FILE *const pFileHandleDataBase, FILE *const pFileHandleErrorLog, const char * pReadStringFromFile, TTeam * pTeamToLoad)
{
//    const char * pDataBaseStartTagForName           = "  <Name>";
    const char * pDataBaseStartTagForCoach          = "  <Trainer>";
    const char * pDataBaseStartTagForPlayer         = "  <Player>";
    const char * pDataBaseStartTagForMatchesWon     = "  <Win>";
    const char * pDataBaseStartTagForMatchesTied    = "  <Tie>";
    const char * pDataBaseStartTagForMatchesLost    = "  <Defeat>";
    const char * pDataBaseStartTagForGoalsScored    = "  <Goals>";
    const char * pDataBaseStartTagForGoalsLetIn     = "  <GuestGoals>";
    const char * pDataBaseStartTagForPoints         = "  <Points>";



    if(strncmp(pReadStringFromFile, STARTTAG_TEAM_NAME, sizeof(STARTTAG_TEAM_NAME) - 1) == 0)
    {
        printf("xml-tag kann man so #definen");
        return 1;
    } else if(strncmp(pReadStringFromFile, pDataBaseStartTagForCoach, sizeof(pDataBaseStartTagForCoach) - 1) == 0)
    {
        return 1;
    } else if(strncmp(pReadStringFromFile, pDataBaseStartTagForPlayer, sizeof(pDataBaseStartTagForPlayer) - 1) == 0)
    {
        if(loadOnePlayer(pFileHandleDataBase, pFileHandleErrorLog, pTeamToLoad->players) == 0)
            return 0;

        return 1;
    } else if(strncmp(pReadStringFromFile, pDataBaseStartTagForMatchesWon, sizeof(pDataBaseStartTagForMatchesWon) - 1) == 0)
    {
        return 1;
    } else if(strncmp(pReadStringFromFile, pDataBaseStartTagForMatchesTied, sizeof(pDataBaseStartTagForMatchesTied) - 1) == 0)
    {
        return 1;
    } else if(strncmp(pReadStringFromFile, pDataBaseStartTagForMatchesLost, sizeof(pDataBaseStartTagForMatchesLost) - 1) == 0)
    {
        return 1;
    } else if(strncmp(pReadStringFromFile, pDataBaseStartTagForGoalsScored, sizeof(pDataBaseStartTagForGoalsScored) - 1) == 0)
    {
        return 1;
    } else if(strncmp(pReadStringFromFile, pDataBaseStartTagForGoalsLetIn, sizeof(pDataBaseStartTagForGoalsLetIn) - 1) == 0)
    {
        return 1;
    } else if(strncmp(pReadStringFromFile, pDataBaseStartTagForPoints, sizeof(pDataBaseStartTagForPoints) - 1) == 0)
    {
        return 1;
    }

    return 0;
}

static short loadOnePlayer(FILE *const pFileHandleDataBase, FILE *const pFileHandleErrorLog, TPlayer * pPlayersToLoad)
{
    char readBuffer[100];

    unsigned short i = 0;


    do
    {
        if(fgets(readBuffer, sizeof(readBuffer), pFileHandleDataBase)/* == NULL      !!!ERRORHANDLING NOCH IMPLEMENTIEREN!!!   */)
        {
            if(loadOnePlayerAttribute(pFileHandleDataBase, pFileHandleErrorLog, readBuffer, &pPlayersToLoad[i]) == 0)
            {
                i++;
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
    } while(strncmp(readBuffer, ENDTAG_TEAM_PLAYER, sizeof(ENDTAG_TEAM_PLAYER)) != 0);

    return 1;
}

static short loadOnePlayerAttribute(FILE *const pFileHandleDataBase, FILE *const pFileHandleErrorLog, const char * pReadStringFromFile, TPlayer* pPlayerToLoad)
{

    if(strncmp(pReadStringFromFile, STARTTAG_TEAM_PLAYER_NAME, sizeof(STARTTAG_TEAM_PLAYER_NAME) - 1) == 0)
    {
        return 1;
    } else if(strncmp(pReadStringFromFile, STARTTAG_TEAM_PLAYER_BIRTHDAY, sizeof(STARTTAG_TEAM_PLAYER_BIRTHDAY) - 1) == 0)
    {
        return 1;
    } else if(strncmp(pReadStringFromFile, STARTTAG_TEAM_PLAYER_JERSEYNUMBER, sizeof(STARTTAG_TEAM_PLAYER_JERSEYNUMBER) - 1) == 0)
    {
        return 1;
    } else if(strncmp(pReadStringFromFile, STARTTAG_TEAM_PLAYER_GOALS, sizeof(STARTTAG_TEAM_PLAYER_GOALS) - 1) == 0)
    {
        return 1;
    }

    return 0;
}
