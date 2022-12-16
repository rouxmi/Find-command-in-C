#include "../includes/listfiles.h"

//pour lister tout les fichiers d'un chemin
void listFilesRecursively(listfile *listfile, char *Path)
{
    // creation du chemin de depart
    char basePath[1000];
    strcpy(basePath, Path);

    

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
            // creation du chemin suivant à partir du chemin de depart
            strcpy(path, basePath);
            if (basePath[strlen(basePath) - 1] != '/'){
                strcat(path, "/");
            }
            strcat(path, dp->d_name);

            //char* fname ="main.c";
            //name(dp->d_name,fname,path);
            //size("-500",path);

            addfile(listfile, path);

            listFilesRecursively(listfile, getlastfile(listfile)->path);
        }
    }
    
    // ferme le chemin
    closedir(dir);
}

