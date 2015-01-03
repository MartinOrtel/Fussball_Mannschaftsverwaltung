#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED


extern void printErrorMessage();

extern short getText(char const *pPrompt, unsigned short maxLengthOfUserInput, unsigned short allowEmptyText, char **ppReturnString);

extern short getNumber(char const *pPrompt, unsigned short *ppReturnNumber, unsigned short lowestNumberAllowed, unsigned short highesNumberAllowed);

extern short askPolarQuestion(char * Prompt);


extern short askAgain();

extern void clearBuffer();

extern void clearScreen();

extern void waitForEnter();

extern void printLine(char printChar, unsigned long lineLength);

extern short terminateApplication();


#endif // TOOLS_H_INCLUDED
