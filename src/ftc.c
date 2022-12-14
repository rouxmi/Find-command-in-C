#include "../includes/ftc.h"

int main(int argc,char *argv[ ]) {
    // check sil y a assez darguments
    if (argc < 2) {
        fprintf(stderr,"Necessite au moins un pwd \n");
        exit(1);
    }
    
    if (argc == 2) {
        //Pas de parametre de recherche
        //listFilesRecursively(argv[1]);
        exit(0);
    }
    
    return 0;
}



