#include "../includes/perm.h"

int getperm(char * file)
{
    struct stat buf;  
    stat(file, &buf);
    int statchmod = buf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
    return statchmod;
}

bool testperm(char* perm, char* path){
    int permint = atoi(perm);
    int fileperm = getperm(path);
    if (permint == fileperm){
        return true;
    }
    return false;
}
