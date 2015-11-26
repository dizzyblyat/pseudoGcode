#include "main.h"

#define buffSize (64)

struct array{
  char *item;
  Array *next;
};


/********************************************
 ********* Misc. printing messages **********
 *******************************************/
void warningTop(){
  puts("\n################# WARNING #################");
}

void warningBottom(){
  puts("###########################################\n");
}

void warningInstruct(){
  puts("\nHow-to: ./gcode *.nc");
  puts("Alt: ./gcode *.nc true");
  puts("\n(\"true\" as the third argument will\nprint the formatted file in the terminal)");
}


/********************************************
 ************* Helper functions *************
 *******************************************/
void readLine(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if (dest[len-1] == '\n'){
    dest[len-1] = '\0';
  }
  if (dest[len-2] == '\r'){
    dest[len-2] = '\0';
  }
}

void memFree(Array *cursor){
  if(cursor == NULL){
    return;
  }

  free(cursor->item);
  memFree(cursor->next);
  cursor->next = NULL;
  
  free(cursor);
  cursor = NULL;
}

void exitProgram(FILE *database){
  fclose(database);
  exit(0);
}

int badInput(int argc, char *argv[]){
  int i = 0;

  while(i < 1){
    char *filename = argv[1];
    // Error messaging
    if(argc < 2){
      warningTop();
      puts("Too few arguments!");
      warningInstruct();
      warningBottom();
      return 1;
    }

    const char *ext = strrchr(filename, '.');
    if(ext == NULL){
      warningTop();
      puts("Wrong filetype (*.nc file required).");
      warningBottom();
      return 1;
    }
    if(ext != NULL){
      if(strcmp(ext, ".nc") != 0){
        warningTop();
        puts("Wrong filetype (*.nc file required).");
        warningBottom();
        return 1;
      }
      else{
        ++i;
      }
    }
    if(argc > 3){
      warningTop();
      puts("Too many arguments!");
      warningInstruct();
      warningBottom();
      return 1;
    }
    if(access(filename, F_OK) == -1 && argc > 1){
      warningTop();
      printf("File \"%s\" does not exist.\n", filename);
      warningBottom();
      return 1;
    }
    else{
      ++i;
    }
  }
  return 0;
}

void filePrint(Array *head){
  while(head != NULL){
    printf("%s\n", head->item);
    head = head->next;
  }
}


/********************************************
 ************** Main functions **************
 *******************************************/
void fileIndex(Array **head, char *buffer)
{
  Array *newNode = malloc(sizeof(Array));

  newNode->item = malloc(strlen(buffer) + 1);
  strcpy(newNode->item, buffer);

  newNode->next = *head;
  *head = newNode;
}

void fileRead(Array **head, FILE *database){
  int setBit = 0;
  int setBit2 = 0;
  char str0[] = ("(Converted with pseudoGcode Version 1.0)");
  char str1[] = ("G0 Z0");
  char str2[] = ("M3");
  char str3[] = ("M5");
  char str4[] = ("G0 X0 Y0\nG0 Z-");
  char buffer[64];
  int homing;


  while(1){
    readLine(buffer, buffSize, database);

    if(feof(database)){
      break;
    }

    const char *ext = strrchr(buffer, 'F');

    if(strcmp(buffer, str0) == 0){
      puts("File has already been formatted by pseudoGcode. Exiting...");
      exitProgram(database);
    }
    
    if(buffer[0] == '(' && setBit2 == 0){
      fileIndex(head, str0);
      fileIndex(head, buffer);
      setBit2 = 1;
    }
    else if(buffer[1] == '1' && buffer[3] == 'Z'){
      int temp1 = buffer[5];
      homing = temp1 - 48 + 1;
      fileIndex(head, buffer); 
    } 
    else if(strcmp(buffer, str1) == 0 && setBit == 0){
      fileIndex(head, "G0 Z-0.2");
      setBit = 1;
    }
    else if(strcmp(buffer, str2) == 0){
    }
    else if(ext != NULL){
      if(strcmp(ext, "F50") == 0 && buffer[3] == 'Z'){
	fileIndex(head, buffer);
	fileIndex(head, str2);
      }
      else{
	fileIndex(head, buffer);
      }
    }
    else if(strcmp(buffer, str1) == 0 && setBit == 1){
      fileIndex(head, str3);
    }
    else if(strcmp(buffer, str3) == 0){
      char temp[8];
      sprintf(temp, "%d", homing);
      fileIndex(head, strcat(str4, temp));
    }
    else{
      fileIndex(head, buffer);
    }
  }
}

void fileReverse(Array **head, int argc, char *argv[]){
  char buffer[64];
  char *filename = argv[1];
  FILE *database = fopen(filename, "r+");

  while(1){
    readLine(buffer, buffSize, database);
    if(feof(database)){
      break;
    }
    fileIndex(head, buffer);
  }
  fclose(database);
}

// Read the input file
int fileOpen(Array **head, int argc, char *argv[]){
  char *filename = argv[1];
  FILE *database = fopen(filename, "r+");
  fileRead(head, database);
  fclose(database);
  return 1;  
}

void fileSave(Array *head, char *argv[]){
  char *filename = argv[1];
  // Open file
  FILE *database = fopen(filename, "r+");
  // Fulsh file
  freopen(filename, "w", database);

  while(head != NULL){
    fprintf(database, "%s\n", head->item);
    head = head->next;
    if(head == NULL){
      break;
    }
  }
  fclose(database);
}

int main(int argc, char *argv[]){
  Array *headR = NULL;
  Array *head = NULL;

  // Check for bad input(s)
  if(badInput(argc, argv) == 1){
    return -1;
  }  

  // Read the input file
  fileOpen(&head, argc, argv);

  // Save to external file
  fileSave(head, argv);

  // Free memory
  memFree(head);

  // Reverse file
  fileReverse(&headR, argc, argv);
  if(argc > 2 && strcmp(argv[2], "true") == 0){
    // Print file
    filePrint(headR);
    puts("");
  }
  fileSave(headR, argv);
  memFree(headR);

  puts("Done!");
  return 0;
}
