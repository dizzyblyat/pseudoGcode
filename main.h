#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef __main_h__
#define __main_h__

typedef struct array Array;

//Misc. print messages
void warningTop();
void warningBottom();
void warningInstruct();
//Helper functions
void readLine(char *dest, int n, FILE *source);
void memFree(Array *cursor);
void exitProgram(FILE *database);
int badInput(int argc, char *argv[]);
void filePrint(Array *head);
//Main functions
void fileIndex(Array **head, char *buffer);
void fileRead(Array **head, FILE *database);
void fileReverse(Array **head, int argc, char *argv[]);
int fileOpen(Array **head, int argc, char *argv[]);
void fileSave(Array *head, char *argv[]);
#endif
