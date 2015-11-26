#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef __main_h__
#define __main_h__

typedef struct array Array;

void readLine(char *dest, int n, FILE *source);
int badInput(int argc, char *argv[]);
void filePrint(Array *head);
void fileIndex(Array **head, char *buffer);
void fileRead(Array **head, FILE *database);
void fileReverse(Array **head, int argc, char *argv[]);
int fileOpen(Array **head, int argc, char *argv[]);
void fileSave(Array *head, char *argv[]);
void memFree(Array *head);
#endif
