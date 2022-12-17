#include "../includes/cat.h"


bool testctc(char* path, char* ctc){
    FILE* ptr=fopen(path,"r");
    char filectc[1000];
    fgets(filectc,1000,ptr);
    printf("%s \n",filectc);
    if (strstr(filectc,ctc) != NULL){
        fclose(ptr);
        return true;
    }
    fclose(ptr);
    return false;
}