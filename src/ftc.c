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
    
    if (argc == 2) {
        //Pas de parametre de recherche
        printf("%s\n", argv[1]);
        listFilesRecursively(argv[1]);
        exit(0);
    }
    
    // parcours les arguments pour parser les options de recherche
    for (int i = 2; i < argc; i = i+2 ) {
        if ( strcmp(argv[i], "-name") == 0 ) {
            printf("choix de nom reconnu avec pour valeur : %s \n", argv[i+1]);
        } else if ( strcmp(argv[i], "-size") == 0 ) {
            printf("choix de taille reconnu avec pour valeur : %s \n", argv[i+1]);
        } else if ( strcmp(argv[i], "-date") == 0 ) {
            printf("choix de date reconnu avec pour valeur : %s \n", argv[i+1]);
        } else if ( strcmp(argv[i], "-mime") == 0 ) {
            printf("choix de mime type reconnu avec pour valeur : %s \n", argv[i+1]);
        } else if ( strcmp(argv[i], "-ctc") == 0 ) {
            printf("choix de ctc reconnu avec pour valeur : %s \n", argv[i+1]);
        } else if ( strcmp(argv[i], "-dir" ) == 0 ) {
            printf("choix de dir reconnu avec pour valeur : %s \n", argv[i+1]);
        //} else if ( strcmp(argv[i], "-test") == 0 ) {
        //    printf("choix de test reconnu avec pour valeur : %s \n", argv[i+1]);
        } else {    
            printf("choix de parametre de recherche inconnu \n");
            exit(1);            
        }
    }    
    return 0;
}



