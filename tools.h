#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

extern void printErrorMessage();

extern short getText(char const *pPrompt, unsigned short maxLengthOfUserInput, unsigned short allowEmptyText, char **ppReturnString);

extern short getNumber(char const *pPrompt, unsigned short *ppReturnNumber, unsigned short lowestNumberAllowed, unsigned short highesNumberAllowed);

extern short askPolarQuestion(char * Prompt);


extern short askAgain();
/************************************************************************************
 * FUNCTION:                askAgain
 *-----------------------------------------------------
 * DESCRIPTION:             Fragt ob der Benutzer die Aktion wiederholen moechte.
 *                          Liest die Eingabe ein und uebergibt einen Wahrheitswert.
 * FIELD OF APPLICATION:    Global
 * PARAMETER:
 * TYP OF RESULT:           unsigned short
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        1, wenn Wiederholung gewuenscht wird
 *                          0, wenn KEINE Wiederholung gewünscht wird
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2013-05-22
 * CHANGES     :            -
 ************************************************************************************/


extern void clearBuffer();
/************************************************************************************
 * FUNCTION:                clearBuffer
 *-----------------------------------------------------
 * DESCRIPTION:             loeschen des STDIN file descriptors
 *
 * FIELD OF APPLICATION:    Global
 * PARAMETER:
 * TYP OF RESULT:           void
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
 *
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2014-xx-xx
 * CHANGES     :            -
 ************************************************************************************/


extern void clearScreen();
/************************************************************************************
 * FUNCTION:                clearScreen
 *-----------------------------------------------------
 * DESCRIPTION:             loeschen des Bildschirminhalts
 *
 * FIELD OF APPLICATION:    Global
 * PARAMETER:
 * TYP OF RESULT:           void
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
 *
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2014-xx-xx
 * CHANGES     :            -
 ************************************************************************************/


extern void waitForEnter();
/************************************************************************************
 * FUNCTION:                waitForEnter
 *-----------------------------------------------------
 * DESCRIPTION:
 *
 * FIELD OF APPLICATION:    Global
 * PARAMETER:
 * TYP OF RESULT:
 * VALUE OF RESULT:
 *   -> NORMAL CASE:
 *
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2014-xx-xx
 * CHANGES     :            -
 ************************************************************************************/


extern void printLine(char printChar, unsigned long lineLength);
/************************************************************************************
 * FUNCTION:                printLine
 *-----------------------------------------------------
 * DESCRIPTION:             erhält ein Zeichen und eine Anzahl als Parameter
 *                          das angegebene Zeichen entsprechend der Anzahl
 *                          mehrmals hintereinander ausgegeben
 *
 * FIELD OF APPLICATION:    Global
 * PARAMETER:
 * TYP OF RESULT:
 * VALUE OF RESULT:
 *   -> NORMAL CASE:
 *
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2014-05-23
 * CHANGES     :            -
 ************************************************************************************/


extern short terminateApplication();
#endif // TOOLS_H_INCLUDED
