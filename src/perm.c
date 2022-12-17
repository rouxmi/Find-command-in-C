#include "../includes/perm.h"

char* getperm(char * file)
{
    struct stat buf;  
    stat(file, &buf);
    int statchmod = buf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
    //convert octal statchmod to string
    char* perm = malloc(4);
    sprintf(perm, "%o", statchmod);
    return perm;
}

bool testperm( char* path,char* perm){
    char* fileperm = getperm(path);
    if (strcmp(perm,fileperm) == 0){
        return true;
    }
    return false;
}
