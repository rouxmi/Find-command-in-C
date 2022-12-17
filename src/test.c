#include "../includes/test.h"

//test si ftc existe
void testftc(){
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
    if (system("./ftc ./ >test.txt") == 0) {
        printf("🟢 ftc: ftc return code 0\n");
    }
    else {
        printf("🔴 ftc: ftc return code 1\n");
        exit(1);
    }
}

//main

int main(int argc,char *argv[ ]) {
    testftc();
    testftcexecutable();
    testftcreturncode();
    return 0;
}
