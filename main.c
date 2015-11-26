#include "main.h"

#define buffSize (32)

struct array{
  char *item;
  Array *next;
};



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

int badInput(int argc, char *argv[]){
  int i = 0;

  while(i < 1){
    char *filename = argv[1];
    const char *ext = strrchr(filename, '.');
    // Error messaging
    if(ext == NULL){
      puts("Wrong filetype (*.nc file required).");
      return 1;
    }
    if(ext != NULL){
      if(strcmp(ext, ".nc") != 0){
        puts("Wrong filetype (*.nc file required).");
        return 1;
      }
      else{
        ++i;
      }
    }
    if(argc < 2){
      puts("You haven't included any .nc file.");
      return 1;
    }
    else if(argc > 2){
      puts("One file at a time, please.");
      return 1;
    }
    if(access(filename, F_OK) == -1 && argc > 1){
      printf("File \"%s\" does not exist.\n", filename);
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
  char str1[] = ("G0 Z0");
  char str1rep1[] = ("G0 Z-0.2");
  char str2[] = ("M3");
  char str3[] = ("M5");
  char str4[] = ("G0 X0 Y0\nG0 Z-2");
  char buffer[32];

  while(1){
    readLine(buffer, buffSize, database);
    if(feof(database)){break;}

    const char *ext = strrchr(buffer, 'F');

    if(strcmp(buffer, str1) == 0 && setBit == 0){
      fileIndex(head, str1rep1);
      setBit = 1;
    }
    else if(strcmp(buffer, str2) == 0){
    }
    else if(ext != NULL){
      if(strcmp(ext, "F50") == 0){
	fileIndex(head, buffer);
	fileIndex(head, str2);
      }
    }
    else if(strcmp(buffer, str1) == 0 && setBit == 1){
      fileIndex(head, str3);
    }
    else if(strcmp(buffer, str3) == 0){
      fileIndex(head, str4);
    }
    else{
      fileIndex(head, buffer);
    }
  }
}

void fileReverse(Array **head, int argc, char *argv[]){
  char buffer[32];
  char *filename = argv[1];
  FILE *database = fopen(filename, "r+");

  while(1){
    readLine(buffer, buffSize, database);
    if(feof(database)){break;}
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

void memFree(Array *head){
  if(head == NULL){
    return;
  }

  while(head != NULL){
    free(head->item);
    free(head);
    head = head->next;
  }
}

int main(int argc, char *argv[]){
  Array *headr = NULL;
  Array *head = NULL;

  // Check for bad input(s)
  if(badInput(argc, argv) == 1){
    return -1;
  }  

  // Read the input file
  fileOpen(&head, argc, argv);

  // Print file
  //filePrint(head);

  // Save to external file
  fileSave(head, argv);

 // Free memory
  memFree(head);

  // Reverse file
  fileReverse(&headr, argc, argv);
  fileSave(headr, argv);
  memFree(headr);
  return 0;
}
