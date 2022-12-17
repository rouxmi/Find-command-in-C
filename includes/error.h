#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "listfiles.h"


void printerror(char* error);

void checkflagtab(tabflag tab);

void checkparam(int argc, char* argv[]);

void checksize(char* size);

void checkdate(char* date);

int getoccurence(char* str,char c);

void checkperm(char* perm);

void checkname(char* name);
