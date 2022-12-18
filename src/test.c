
#include "../includes/test.h"

//test si ftc existe
void testftc(){
    printf("test ftc exist:\n");
    if (access("ftc", F_OK) == -1) {
        printf("🔴 ftc: ftc not found\n");
        exit(1);
    }
    else {
        printf("🟢 ftc: ftc found\n");
    }
}

//test si ftc est executable
void testftcexecutable(){
    printf("test ftc executable:\n");
    if (access("ftc", X_OK) == -1) {
        printf("🔴 ftc: ftc not executable\n");
        exit(1);
    }
    else {
        printf("🟢 ftc: ftc executable\n");
    }
}

//test si ftc retourne 0
void testftcreturncode(){
    printf("test ftc return code:\n");
    if (system("./ftc ./ >test.txt") == 0) {
        printf("🟢 ftc: ftc return code 0\n");
    }
    else {
        printf("🔴 ftc: ftc return code 1\n");
        exit(1);
    }
}

//test si ftc prend bien les flags
void testftcflag(){
    printf("test ftc flag:\n");
    system("./ftc ./ -name 'src' -size '+9k' -perm '564' -color -test -dir 'oui' -ctc 'ok' -mime 'app'>test.txt");
    FILE* file = fopen("test.txt", "r");
    char line[2056];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    if (count == 6) {
        printf("🟢 ftc: ftc take flag\n");
    }
    else {
        printf("🔴 ftc: ftc don't take flag\n");
        exit(1);
    }
}

//test si ftc name retourne le bon nombre de fichier
void testftcname(){
    printf("test ftc name:\n");
    system("./ftc ./ -name src >test.txt");
    FILE* file = fopen("test.txt", "r");
    int count = 0;
    char line[2056];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    
    if (count == 12) {
        printf("🟢 ftc: ftc name return %d files\n",count);
    }
    else {
        printf("🔴 ftc: ftc name return %d files not 12\n",count);
        exit(1);
    }
}

void testftcnamefaux(){
    printf("test ftc name faux, erreur expecté:\n");
    system("./ftc ./ -name src% >test.txt");
    FILE* file = fopen("test.txt", "r");
    int count = 0;
    char line[2056];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    if (count != 0) {
        printf("🔴 ftc: ftc name didn't found the Error\n");
        exit(1);
    }
    else {
        printf("🟢 ftc: ftc name found the Error\n");
    }
}


//test si ftc size retourne le bon nombre de fichier
void testftcsize(){
    printf("test ftc size:\n");
    system("./ftc ./src -size +9k >test.txt");
    FILE* file = fopen("test.txt", "r");
    int count = 0;
    char line[2056];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    if (count == 2) {
        printf("🟢 ftc: ftc size return %d files\n",count);
    }
    else {
        printf("🔴 ftc: ftc size return %d files not 2\n",count);
        exit(1);
    }
}

void testftcsizefaux(){
    printf("test ftc size faux, erreur expecté:\n");
    system("./ftc ./ -size +9p >test.txt");
    FILE* file = fopen("test.txt", "r");
    int count = 0;
    char line[2056];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    if (count != 0) {
        printf("🔴 ftc: ftc size didn't found the Error\n");
        exit(1);
    }
    else {
        printf("🟢 ftc: ftc size found the Error\n");
    }
}

void testftcsizefaux2(){
    printf("test 2 ftc size faux, erreur expecté:\n");
    system("./ftc ./ -size pou >test.txt");
    FILE* file = fopen("test.txt", "r");
    int count = 0;
    char line[2056];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    if (count != 0) {
        printf("🔴 ftc: ftc size didn't found the Error\n");
        exit(1);
    }
    else {
        printf("🟢 ftc: ftc size found the Error\n");
    }
}

//test si ftc date retourne le bon nombre de fichier
void testftcdate(){
    printf("test ftc date:\n");
    system("./ftc ./ -date +1j >test.txt");
    FILE* file = fopen("test.txt", "r");
    int count = 0;
    char line[2056];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    if (count >= 2) {
        printf("🟢 ftc: ftc date return %d files\n",count);
    }
    else {
        printf("🔴 ftc: ftc date only return %d files\n",count);
        exit(1);
    }
}

void testftcdatefaux(){
    printf("test ftc date faux, erreur expecté:\n");
    system("./ftc ./ -date +1j3j >test.txt");
    FILE* file = fopen("test.txt", "r");
    int count = 0;
    char line[2056];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    if (count != 0) {
        printf("🔴 ftc: ftc date didn't found the Error\n");
        exit(1);
    }
    else {
        printf("🟢 ftc: ftc date found the Error\n");
    }
}

void testftcdatefaux2(){
    printf("test 2 ftc date faux, erreur expecté:\n");
    system("./ftc ./ -date 76p >test.txt");
    FILE* file = fopen("test.txt", "r");
    int count = 0;
    char line[2056];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    if (count != 0) {
        printf("🔴 ftc: ftc date didn't found the Error\n");
        exit(1);
    }
    else {
        printf("🟢 ftc: ftc date found the Error\n");
    }
}

//test si ftc -dir retourne le bon nombre de fichier
void testftcdir(){
    printf("test ftc dir:\n");
    system("./ftc ./ -dir >test.txt");
    FILE* file = fopen("test.txt", "r");
    int count = 0;
    char line[2056];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    if (count >= 225) {
        printf("🟢 ftc: ftc dir return %d files\n",count);
    }
    else {
        printf("🔴 ftc: ftc dir return %d files not more than 225\n",count);
        exit(1);
    }
}

//test si ftc perm retourne le bon nombre de fichier
void testftcperm(){
    printf("test ftc perm:\n");
    system("./ftc ./ -perm 700 >test.txt");
    FILE* file = fopen("test.txt", "r");
    int count = 0;
    char line[2056];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    if (count == 0) {
        printf("🟢 ftc: ftc perm return %d files\n",count);
    }
    else {
        printf("🔴 ftc: ftc perm return %d files not 0\n",count);
        exit(1);
    }
}

void testftcpermfaux(){
    printf("test ftc perm faux, erreur expecté:\n");
    system("./ftc ./ -perm 780 >test.txt");
    FILE* file = fopen("test.txt", "r");
    int count = 0;
    char line[2056];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    if (count != 0) {
        printf("🔴 ftc: ftc perm didn't found the Error\n");
        exit(1);
    }
    else {
        printf("🟢 ftc: ftc perm found the Error\n");
    }
}

void testftcpermfaux2(){
    printf("test 2 ftc perm faux, erreur expecté:\n");
    system("./ftc ./ -perm 71 >test.txt");
    FILE* file = fopen("test.txt", "r");
    int count = 0;
    char line[2056];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    if (count != 0) {
        printf("🔴 ftc: ftc perm didn't found the Error\n");
        exit(1);
    }
    else {
        printf("🟢 ftc: ftc perm found the Error\n");
    }
}

//test si ftc mime retourne le bon nombre de fichier
void testftcmime(){
    printf("test ftc mime:\n");
    system("./ftc ./ -mime text/plain >test.txt");
    FILE* file = fopen("test.txt", "r");
    int count = 0;
    char line[2056];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    if (count == 1) {
        printf("🟢 ftc: ftc mime return %d files\n",count);
    }
    else {
        printf("🔴 ftc: ftc mime return %d files not 1\n",count);
        exit(1);
    }
}

void testftcmimefaux(){
    printf("test ftc mime faux, erreur expecté:\n");
    system("./ftc ./ -mime tzqut >test.txt");
    FILE* file = fopen("test.txt", "r");
    int count = 0;
    char line[2056];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    if (count != 0) {
        printf("🔴 ftc: ftc mime didn't found the Error\n");
        exit(1);
    }
    else {
        printf("🟢 ftc: ftc mime found the Error\n");
    }
}

//test si ftc ctc retourne le bon nombre de fichier

void testftcctc(){
    printf("test ftc ctc:\n");
    system("./ftc ./ -ctc ok >test.txt");
    FILE* file = fopen("test.txt", "r");
    int count = 0;
    char line[2056];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    if (count == 29) {
        printf("🟢 ftc: ftc ctc return %d files\n",count);
    }
    else {
        printf("🔴 ftc: ftc ctc return %d files not 29\n",count);
        exit(1);
    }
}

//main

int main(int argc,char *argv[ ]) {
    testftc();
    testftcexecutable();
    testftcreturncode();
    testftcflag();
    testftcname();
    testftcnamefaux();
    testftcsize();
    testftcsizefaux();
    testftcsizefaux2();
    testftcdate();
    testftcdatefaux();
    testftcdatefaux2();
    testftcdir();
    testftcperm();
    testftcpermfaux();
    testftcpermfaux2();
    testftcmime();
    testftcmimefaux();
    testftcctc();
    return 0;
}
