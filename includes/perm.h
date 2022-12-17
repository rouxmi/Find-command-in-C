#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <regex.h>
#include <stdbool.h>

int getperm(char *name);

bool testperm(char* perm, char* path);
