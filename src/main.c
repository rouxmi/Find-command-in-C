#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[ ]) {
    // check s'il y a assez d'arguments
    if (argc < 4) {
        fprintf(stderr,"Necessite au moins un pwd et une option de recherche\n");
        exit(1);
    }
    
    // char* search_dir = argv[1];  --a decommenter quand y en aura besoin

    // parcours les arguments pour parser les options de recherche
    for (int i = 2; i < argc; i = i+2 ) {
        if ( strcmp(argv[i], "-name") == 0 ) {
            printf("choix de nom reconnu avec pour valeur : %s \n", argv[i+1]);
        } else if ( strcmp(argv[i], "-size") == 0 ) {
            printf("choix de taille reconnu avec pour valeur : %s \n", argv[i+1]);
        } else if ( strcmp(argv[i], "-date") == 0 ) {
            printf("choix de date reconnu avec pour valeur : %s \n", argv[i+1]);
        } else if ( strcmp(argv[i], "-mime") == 0 ) {
            printf("choix de mime reconnu avec pour valeur : %s \n", argv[i+1]);
        } else if ( strcmp(argv[i], "-ctc") == 0 ) {
            printf("choix de ctc reconnu avec pour valeur : %s \n", argv[i+1]);
        } else if ( strcmp(argv[i], "-dir" ) == 0 ) {
            printf("choix de dir reconnu avec pour valeur : %s \n", argv[i+1]);
        } else if ( strcmp(argv[i], "-test") == 0 ) {
            printf("choix de test reconnu avec pour valeur : %s \n", argv[i+1]);
        } else {    
            printf("choix de parametre de recherche inconnu \n");
            exit(1);            
        }
    }    
    return 0;
}

