#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../includes/name.h"
#include "../includes/size.h"



typedef struct flag {
    bool isflag;
    char* flagname;
    char* flagvalue;
} flag;

typedef struct tabflag {
    struct flag* tab;
    int size;
} tabflag;


typedef struct listfile {
    char* path;
    struct listfile* next;
} listfile;



tabflag getflag(int mainargc,char *mainargv[ ]);

void printtabflags(tabflag tab);

void printlistfile(listfile* listfile);

void addfile(listfile* listfile,char* path);

listfile* getlastfile(listfile* listfile);

listfile* initializeListFile(char* root);

listfile* callflag(tabflag flagstab, listfile* listfile);

void deleteListFile(listfile* listfile,char* root);

listfile* flagname(char* name, listfile* listoffile);

listfile* flagsize(char* size, listfile* listoffile);
