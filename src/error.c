#include "../includes/error.h"


void printerror(char* error){
    fprintf(stderr, "\x1b[31mError:%s\x1b[0m\n", error);
}

void checkparam(int argc, char* argv[]){
    if (argc < 2){
        printerror("ftc: at least a path is required");
        exit(1);
    }
}

void checkflagtab(tabflag tab){
    for (int i = 0; i < tab.size; i++) {
        if (tab.tab[i].isflag == false) {
            char *error=NULL;
            sprintf(error,"ftc: invalid flag :%s",tab.tab[i].flagname);
            printerror(error);
        }
        if (tab.tab[i].flagvalue==NULL){
            if (strcmp(tab.tab[i].flagname,"-dir")!=0 && strcmp(tab.tab[i].flagname,"-color")!=0 && strcmp(tab.tab[i].flagname,"-test")!=0){
                char* error=NULL;
                sprintf(error,"ftc: flag value required for flag:%s",tab.tab[i].flagname);
                printerror(error);
            }
        }
    }
}

void checksize(char* size){
    if (size[0] == '+' || size[0] == '-') {
        for (int i = 1; i < strlen(size)-1; i++) {
            if (size[i] < '0' || size[i] > '9') {            
                if (size[i] < 'a' || size[i] > 'z') {
                    if (size[i] < 'A' || size[i] > 'Z') {
                        printerror("ftc: invalid size");
                        exit(1);
                    }
                }
            }
        }
    } else {
        for (int i = 0; i < strlen(size)-1; i++) {
            if (size[i] < '0' || size[i] > '9') {
                printerror("ftc: invalid size");
                exit(1);
            }
        }
    }
}

