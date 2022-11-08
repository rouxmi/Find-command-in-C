#include "../includes/name.h"

void name(char* name, char* file,char* path){
    if (strcmp(name,file) ==0){
        printf("le nom colle : %s\n",path);
    }
}
