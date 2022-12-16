#include "../includes/ftc.h"


int main(int argc,char *argv[ ]) {
    // check sil y a assez darguments
    if (argc < 2) {
        fprintf(stderr,"Necessite au moins un pwd \n");
        exit(1);
    }
    
    // check si on ajoute un paramatre pour les options par parité du nombre d'arguments (c'est pas opti, check pas si le param est bon)
    if (argc%2 == 1) {
        fprintf(stderr,"Necessite une valeur pour le parametre de recherche \n");
        exit(1);
    }
    
    
    // parcours les arguments pour parser les options de recherche
    tabflag tab=getflag(argc,argv);

    //parcours les fichiers et les ajoute a la liste
    listfile* listfile=initializeListFile(argv[1]);
    listFilesRecursively(listfile, argv[1]);
    
    if (argc == 2) {
        //Pas de parametre de recherche
        printlistfile(listfile);
        exit(0);
    }
    listfile=callflag(tab,listfile);
    printlistfile(listfile);
    
    //free la liste de fichier et le tableau de flag
    deleteListFile(listfile,argv[1]);
    free(tab.tab);
    return 0;
}



