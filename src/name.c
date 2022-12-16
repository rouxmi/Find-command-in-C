#include "../includes/name.h"

bool testname(char* name, char* path){
    char* file = basename(path);
    if (strcmp(name,file) ==0){
        return true;
    }
    else{
        return false;
    }
}


