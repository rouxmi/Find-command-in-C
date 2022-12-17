#ifndef UNTITLED_DATE_H
#define UNTITLED_DATE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>

double get_last_modification(const char *path);

bool testdate(char* name, char* inputDuration);

#endif //UNTITLED_DATE_H
