#include "../includes/link.h"

char* linker(char * path) {
    char buf[PATH_MAX]; /* PATH_MAX incudes the \0 so +1 is not required */
    char *res = realpath("this_source.c", buf);
    if (res != NULL) { 
        return buf;
    } else {
        return path;
    }
}