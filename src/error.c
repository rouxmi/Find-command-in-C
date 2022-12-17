#include "../includes/error.h"


void printerror(char* error){
    fprintf(stderr, "\x1b[31mError %s\x1b[0m\n", error);
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
                if ((size[i] > 'a' && size[i] < 'z')||(size[i] > 'A' || size[i] < 'Z')) {
                    printerror("ftc: invalid size (must be (+)XbXkXmXg)");
                    exit(1);
                }
            }
        }
    } else {
        for (int i = 0; i < strlen(size)-1; i++) {
            if (size[i] < '0' || size[i] > '9') {
                printerror("ftc: invalid size (must be (+)XbXkXmXg)");
                exit(1);
            }
        }
    }
}

//verifie si la permision est au format : (+)XjXhXm
void checkdate(char* date){
    if (strcmp(date,"today")==0 || strcmp(date,"yesterday")==0 || strcmp(date,"this month")==0 || strcmp(date,"this week")==0 || strcmp(date,"this year")==0){
        return;
    }
    if (getoccurence(date, 'j') > 1 || getoccurence(date, 'h') > 1 || getoccurence(date, 'm') > 1) {
        printerror("ftc: invalid date (must be (+)XjXhXm)");
        exit(1);
    }
    if (date[0] == '+' || date[0] == '-') {
        for (int i = 1; i < strlen(date)-1; i++) {
            if (date[i] < '0' || date[i] > '9') {
                if (date[i] != 'j' && date[i] != 'h' && date[i] != 'm') {
                    printerror("ftc: invalid date (must be (+)XjXhXm)");
                    exit(1);
                }
            }
        }
    } else {
        for (int i = 0; i < strlen(date)-1; i++) {
            if (date[i] < '0' || date[i] > '9') {
                if (date[i] != 'j' && date[i] != 'h' && date[i] != 'm') {
                    printerror("ftc: invalid date (must be XjXhXm)");
                    exit(1);
                }
            }
        }
    }
}

int getoccurence(char* str,char c){
    int occurence=0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == c) {
            occurence++;
        }
    }
    return occurence;
}

//verifie si la permision est au format octal : XXX
void checkperm(char* perm){
    if (strlen(perm) != 3) {
        printerror("ftc: invalid permission (must be 3 digits)");
        exit(1);
    }
    for (int i = 0; i < strlen(perm); i++) {
        if (perm[i] < '0' || perm[i] > '7') {
            printerror("ftc: invalid permission (must be octal)");
            exit(1);
        }
    }
}

//verifie que le nom du fichier ne contient pas de caractere speciaux ou ne commence pas par un point ou chiffre
void checkname(char* name){
    if (name[0] == '.' || name[0] == '0' || name[0] == '1' || name[0] == '2' || name[0] == '3' || name[0] == '4' || name[0] == '5' || name[0] == '6' || name[0] == '7' || name[0] == '8' || name[0] == '9') {
        printerror("ftc: invalid name for file (start with a letter)");
        exit(1);
    }
    for (int i = 0; i < strlen(name); i++) {
        if (name[i] == '/' || name[i] == '*' || name[i] == '?' || name[i] == '[' || name[i] == ']' || name[i] == '{' || name[i] == '}' || name[i] == '|' || name[i] == '\\' || name[i] == '<' || name[i] == '>' || name[i] == '"' || name[i] == '\'' || name[i] == '`' || name[i] == '!' || name[i] == '@' || name[i] == '#' || name[i] == '$' || name[i] == '%' || name[i] == '^' || name[i] == '&' || name[i] == '(' || name[i] == ')' || name[i] == '-' || name[i] == '+' || name[i] == '=' || name[i] == ';' || name[i] == ':' || name[i] == ',' || name[i] == '~') {
            printerror("ftc: invalid name for file (contains special character)");
            exit(1);
        }
    }
}

