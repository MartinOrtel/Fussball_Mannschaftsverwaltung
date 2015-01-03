#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

unsigned short calcDivisionRemainder(char *pText);

TListElement *searchForPlayer(THashElement *aIndex, short (*compare)(const TPlayer *, const TPlayer *), const TPlayer *pPlayerSearchedFor);

#endif // SEARCH_H_INCLUDED
