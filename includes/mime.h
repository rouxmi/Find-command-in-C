#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#ifndef MIME_H
#define MIME_H
enum
{
    EXTENSION_POS,
    MIME_TYPE,
    ARRAY_SIZE,
};

extern char *Mime_types[][ARRAY_SIZE];

char *get_mime_type(char *filename);
bool testmime(char* mime, char* path);

#endif