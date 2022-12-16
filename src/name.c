#include "../includes/name.h"

bool testname(char* name, char* path){
    char* file = basename(path);
    if (strcmp(name,file) ==0){
        return true;
    }
    else{
        regex_t regex;
        int return_value = regcomp(&regex,name,0);
        return_value = regexec(&regex, path, 0, NULL, 0);
        regfree(&regex);
        if(return_value == 0){
            return true;
        }
        return false;
    }
}


