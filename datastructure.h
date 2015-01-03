#ifndef DATASTRUCTURE_H_INCLUDED
#define DATASTRUCTURE_H_INCLUDED

#define MAXTEAMS 10
//unsigned const short MAXPLAYER = 23;
#define MAXPLAYER 23
#define MAXNAMELENGTH 50
#define MAXINDEX 307

typedef struct
{
   unsigned short day;
   unsigned short month;
   unsigned short year;
} TDate;

typedef struct
{
   char* nameOfPlayer;
   TDate* birthday;
   unsigned short jerseyNumber;
   unsigned short numberOfGoals;
} TPlayer;

typedef struct sTeam
{
   char* nameOfTeam;
   char* nameOfCoach;
   unsigned short playerCount;
   TPlayer players[MAXPLAYER + 1];
   unsigned short numberOfMatchesWon;
   unsigned short numberOfMatchesTied;
   unsigned short numberOfMatchesLost;
   unsigned short numberOfGoalsScored;
   unsigned short numberOfGoalsLetIn;
   unsigned short numberOfPoints;
   struct sTeam *pPreviousTeamInDVList;
   struct sTeam *pNextTeamInDVList;
} TTeam;

typedef struct sListElement
{
   TTeam *pTeam;
   TPlayer *pPlayer;
   struct sListElement *pNextListElement;
} TListElement;

typedef struct
{
   TListElement *pFirstListElement;
   TListElement *pLastListElement;
} THashElement;


extern unsigned long globalTeamCounter;
extern TTeam *pFirstTeamInDVList, *pLastTeamInDVList;
extern THashElement aPlayerIndex[];

// database define
#define STARTTAG_START  "<Daten>"
#define STARTTAG_TEAM   " <Team>"
#define STARTTAG_TEAM_NAME "  <Name>"
#define STARTTAG_TEAM_COACH "  <Trainer>"
#define STARTTAG_TEAM_PLAYER "  <Player>"
#define STARTTAG_TEAM_PLAYER_NAME "   <Name>"
#define STARTTAG_TEAM_PLAYER_BIRTHDAY "   <Birthday>"
#define STARTTAG_TEAM_PLAYER_JERSEYNUMBER "   <TricotNr>"
#define STARTTAG_TEAM_PLAYER_GOALS "   <Goals>"
#define STARTTAG_TEAM_MATCHESWON "  <Win>"
#define STARTTAG_TEAM_MATCHESTIED "  <Tie>"
#define STARTTAG_TEAM_MATCHESLOST "  <Defeat>"
#define STARTTAG_TEAM_GOALS "  <Goals>"
#define STARTTAG_TEAM_GOALSLETIN "  <GuestGoals>"
#define STARTTAG_TEAM_POINTS "  <Points>"

#define ENDTAG_END  "</Daten>"
#define ENDTAG_TEAM   " </Team>"
#define ENDTAG_TEAM_NAME "</Name>"
#define ENDTAG_TEAM_COACH "</Trainer>"
#define ENDTAG_TEAM_PLAYER "  </Player>"
#define ENDTAG_TEAM_PLAYER_NAME "</Name>"
#define ENDTAG_TEAM_PLAYER_BIRTHDAY "</Birthday>"
#define ENDTAG_TEAM_PLAYER_JERSEYNUMBER "</TricotNr>"
#define ENDTAG_TEAM_PLAYER_GOALS "</Goals>"
#define ENDTAG_TEAM_MATCHESWON "</Win>"
#define ENDTAG_TEAM_MATCHESTIED "</Tie>"
#define ENDTAG_TEAM_MATCHESLOST "</Defeat>"
#define ENDTAG_TEAM_GOALS "</Goals>"
#define ENDTAG_TEAM_GOALSLETIN "</GuestGoals>"
#define ENDTAG_TEAM_POINTS "</Points>"

#endif // DATASTRUCTURE_H_INCLUDED
