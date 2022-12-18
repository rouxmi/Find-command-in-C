#include "../includes/ftc.h"


int main(int argc,char *argv[ ]) {
    // check sil y a assez darguments
    checkparam(argc,argv);
    // parcours les arguments pour parser les options de recherche
    tabflag tab=getflag(argc,argv);
    checkflagtab(tab);
    

    //parcours les fichiers et les ajoute a la liste
    listfile* listfile=initializeListFile(argv[1]);
    listFilesRecursively(listfile, argv[1]);
    

    //Pas de parametre de recherche
    if (argc == 2) {
        printlistfile(listfile);
        exit(0);
    }     
    //parcours les options de recherche
    listfile=callflag(tab,listfile);
    printlistfile(listfile);
    
    //free la liste de fichier et le tableau de flag
    deleteListFile(listfile,argv[1]);
    free(tab.tab);
    return 0;
}



