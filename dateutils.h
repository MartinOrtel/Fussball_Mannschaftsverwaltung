#ifndef DATEUTILS_H_INCLUDED
#define DATEUTILS_H_INCLUDED
#include "datastructure.h"

/*
unsigned short isLeapYear(int year);
***********************************************************************************
 * FUNCTION:                isLeapYear
 *-----------------------------------------------------
 * DESCRIPTION:             nimmt eine Jahreszahl und gibt als Wahrheitswert zurueck
 *                          ob es sich um ein Schaltjahr handelt
 * FIELD OF APPLICATION:    Global
 * PARAMETER:
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        1, es ist ein Schaltjahr
 *                          0, es ist KEIN Schaltjahr
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2014-xx-xx
 * CHANGES     :            -
 ************************************************************************************/

/*
unsigned short isDateValid(TDate const * pDate);
***********************************************************************************
 * FUNCTION:                isDateValid
 *-----------------------------------------------------
 * DESCRIPTION:             nimmt Tag, Monat, Jahr als int und
 *                          gibt als Wahrheitswert zurueck ob das Datum gueltig ist
 * FIELD OF APPLICATION:    Global
 * PARAMETER:
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        1, es ist ein gueltiges Datum
 *                          0, es ist KEIN gueltiges Datum
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2014-xx-xx
 * CHANGES     :            -
 ************************************************************************************/


extern short getDateFromString(char const *pUserInput, TDate *pReturnDate);
/***********************************************************************************
 * FUNCTION:                getDateFromString
 *-----------------------------------------------------
 * DESCRIPTION:             nimmt einen Datum als String und parst den jeweiligen
                            Tag, Monat und das Jahr und schreibt sie in die dafuer
 *                          uebergebene Zeiger
 * FIELD OF APPLICATION:    Global
 * PARAMETER:
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        1
 *
 *   -> FAULT  CASE:        0
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2014-xx-xx
 * CHANGES     :            -
 ************************************************************************************/


extern short getDate(char const *pPrompt, TDate **ppReturnDate);
/************************************************************************************
 * FUNCTION:                getDate
 *-----------------------------------------------------
 * DESCRIPTION:             fordert den Benutzer auf ein Datum einzugeben
 *                          ueberprueft das Datum auf Gueltigkeit
 *                          Gueltiges Datum wird in die dafuer uebergebene Zeiger
 *                          geschrieben
 * FIELD OF APPLICATION:    Global
 * PARAMETER:
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        1
 *
 *   -> FAULT  CASE:        0
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2014-xx-xx
 * CHANGES     :            -
 ************************************************************************************/



#endif // DATEUTILS_H_INCLUDED
