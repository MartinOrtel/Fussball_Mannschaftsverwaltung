#ifndef DATEUTILS_H_INCLUDED
#define DATEUTILS_H_INCLUDED
#include "datastructure.h"


extern short getDateFromString(char const *pUserInput, TDate *pReturnDate);

extern short getDate(char const *pPrompt, TDate **ppReturnDate);


#endif // DATEUTILS_H_INCLUDED
