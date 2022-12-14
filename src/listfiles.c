#include "../includes/listfiles.h"

//pour lister tout les fichiers d'un chemin
void listFilesRecursively(char *basePath)
{

    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    // impossible d'ouvrir le chemin (fichier)
    if (!dir)
        return;

    
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            
            // création du chemin suivant à partir du chemin de départ
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            //char* fname ="main.c";
            //name(dp->d_name,fname,path);
            //size("-500",path);

            //print les chemins 
            printf("%s\n", path);

            listFilesRecursively(path);
        }
    }
    
    // ferme le chemin
    closedir(dir);
}
