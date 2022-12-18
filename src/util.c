#include "../includes/util.h"

bool dir_mode=false;
bool threads_mode=false;
int threads_number=0;
bool color_mode=false;
bool link_mode=false;
bool or_mode=false;

//fonction qui permet de savoir si un fichier est un répertoire ou un fichier

bool is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode)==1;
}

bool is_directory(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode)==1;
}

//fonction qui permet de gérer les flags


tabflag getflag(int mainargc,char *mainargv[ ]){
    tabflag tab;
    tab.size=0;
    tab.tab=malloc(sizeof(flag));
    for (int i = 2; i < mainargc; i = i+2) {
        if ( strcmp(mainargv[i], "-name") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-name";
            checkname(mainargv[i+1]);
            tab.tab[tab.size].flagvalue=mainargv[i+1];
            tab.size++;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        } else if ( strcmp(mainargv[i], "-size") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-size";
            checksize(mainargv[i+1]);
            tab.tab[tab.size].flagvalue=mainargv[i+1];
            tab.size++;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        } else if ( strcmp(mainargv[i], "-date") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-date";
            checkdate(mainargv[i+1]);
            tab.tab[tab.size].flagvalue=mainargv[i+1];
            tab.size++;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        } else if ( strcmp(mainargv[i], "-mime") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-mime";
            checkmimetype(mainargv[i+1]);
            tab.tab[tab.size].flagvalue=mainargv[i+1];
            tab.size++;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        } else if ( strcmp(mainargv[i], "-ctc") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-ctc";
            tab.tab[tab.size].flagvalue=mainargv[i+1];
            tab.size++;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        }else if ( strcmp(mainargv[i], "-perm") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-perm";
            checkperm(mainargv[i+1]);
            tab.tab[tab.size].flagvalue=mainargv[i+1];
            tab.size++;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        }else if ( strcmp(mainargv[i], "-threads") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-threads";
            tab.tab[tab.size].flagvalue=mainargv[i+1];
            tab.size++;
            threads_mode = true;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        }else if ( strcmp(mainargv[i], "-dir" ) == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-dir";
            if (i+1<mainargc)
            {
                if (mainargv[i+1][0] == '-'){
                    tab.tab[tab.size].flagvalue=NULL;
                    i--;
                }else {
                    checkname(mainargv[i+1]);
                    tab.tab[tab.size].flagvalue=mainargv[i+1];
                }
            }
            else {
                tab.tab[tab.size].flagvalue=NULL;
            }
            tab.size++;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        } else if ( strcmp(mainargv[i], "-test") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-test";
            tab.tab[tab.size].flagvalue=NULL;
            tab.size++;
            i--;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        }else if ( strcmp(mainargv[i], "-color") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-color";
            tab.tab[tab.size].flagvalue=NULL;
            color_mode=true;
            tab.size++;
            i--;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        }else if ( strcmp(mainargv[i], "-link") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-link";
            tab.tab[tab.size].flagvalue=NULL;
            link_mode=true;
            tab.size++;
            i--;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        }else if ( strcmp(mainargv[i], "-ou") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-ou";
            tab.tab[tab.size].flagvalue=NULL;
            or_mode=true;
            tab.size++;
            i--;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        }else {    
            printf("Le flag %s n'est pas correct\n", mainargv[i]);
            exit(1);
        }
    }
    return tab;
}


void printtabflags(tabflag flagstab){
    for(int i=0; i<flagstab.size;i++){
        if(flagstab.tab[i].isflag && flagstab.tab[i].flagvalue!=NULL){
            printf("La valeur du flag %s est %s\n",flagstab.tab[i].flagname,flagstab.tab[i].flagvalue);
        }
    }
}

//fonction qui permet de gérer listfile


void addfile(listfile* listfile,char* path){
    while(listfile->next!=NULL){
        listfile=listfile->next;
    }
    listfile->next=malloc(sizeof(listfile)*2);
    listfile->next->path=malloc(strlen(path)+1);
    if (link_mode){
        strcpy(listfile->next->path,linker(path));
    } else{
        strcpy(listfile->next->path,path);
    }
    listfile->next->next=NULL;
}


listfile* getlastfile(listfile* listfile){
    while(listfile->next!=NULL){
        listfile=listfile->next;
    }
    return listfile;
}

//fonction de savoir si un fichier est déjà dans la liste
bool isfileinlist(listfile* listfile,char* Path){
    while(listfile!=NULL){
        if (strcmp(listfile->path,Path)==0){
            return true;
        }
        listfile=listfile->next;
    }
    return false;
} 


void printlistfile(listfile* listfile){
    while(listfile!=NULL){
        if (strcmp(listfile->path,"end")!=0){
            if(color_mode){
                if (is_directory(listfile->path)){
                    printf("\x1b[33m%s/\x1b[36m%s\n",dirname(listfile->path),basename(listfile->path));
                } else {
                    printf("\x1b[33m%s/\x1b[32m%s\n",dirname(listfile->path),basename(listfile->path));
                }
            } else {
                printf("%s\n",listfile->path);
            }
        }
        listfile=listfile->next;
    }
}

listfile* initializeListFile(char* root){
    listfile* listfile = malloc(sizeof(listfile)*10);
    listfile->path="end";
    listfile->next=NULL;
    addfile(listfile,root);
    return listfile;
}


void deleteListFile(listfile* listfile, char* root){
    if(listfile->next!=NULL){
        deleteListFile(listfile->next,root); 
    }
    if (strcmp(listfile->path,"end")!=0){
        free(listfile->path);
    }
    free(listfile);
    
    
}

//Appel des différentes fonctions en fonction des flags

//call the function depending on the flag
listfile* callflag(tabflag flagstab, listfile* Listfile){
    if (!or_mode){
        //si on est en mode and
        for(int i=0; i<flagstab.size;i++){
            if(flagstab.tab[i].isflag){
                if(strcmp(flagstab.tab[i].flagname,"-name")==0){
                    Listfile=flagname(flagstab.tab[i].flagvalue,Listfile);
                }else if(strcmp(flagstab.tab[i].flagname,"-size")==0){
                    Listfile=flagsize(flagstab.tab[i].flagvalue,Listfile);
                }else if(strcmp(flagstab.tab[i].flagname,"-date")==0){
                    Listfile=flagdate(flagstab.tab[i].flagvalue,Listfile);
                }else if(strcmp(flagstab.tab[i].flagname,"-mime")==0){
                    Listfile=flagmime(flagstab.tab[i].flagvalue,Listfile);
                }else if(strcmp(flagstab.tab[i].flagname,"-ctc")==0){
                    Listfile=flagctc(flagstab.tab[i].flagvalue,Listfile);
                }else if(strcmp(flagstab.tab[i].flagname,"-dir")==0){
                    dir_mode=true;
                    if (flagstab.tab[i].flagvalue!=NULL){
                        Listfile=flagdir(Listfile,flagstab.tab[i].flagvalue);
                    }else{
                        Listfile=flagdir(Listfile,NULL);
                    }
                }else if(strcmp(flagstab.tab[i].flagname,"-perm")==0){
                    Listfile=flagperm(flagstab.tab[i].flagvalue,Listfile);
                }else if(strcmp(flagstab.tab[i].flagname,"-test")==0){
                    printtabflags(flagstab);
                    exit(1);
                }
            }
        }
        return Listfile;
    }else{
        
        //si on est en mode or entre les flags
        listfile* listfile2 = malloc(sizeof(Listfile)*10);
        listfile2->path=Listfile->path;
        listfile2->next=NULL;
        listfile* adresselist = Listfile;
        for(int i=0; i<flagstab.size;i++){

            if(flagstab.tab[i].isflag){
                if(strcmp(flagstab.tab[i].flagname,"-name")==0){
                    Listfile=flagname(flagstab.tab[i].flagvalue,adresselist);
                }else if(strcmp(flagstab.tab[i].flagname,"-size")==0){
                    Listfile=flagsize(flagstab.tab[i].flagvalue,adresselist);
                }else if(strcmp(flagstab.tab[i].flagname,"-date")==0){
                    Listfile=flagdate(flagstab.tab[i].flagvalue,adresselist);
                }else if(strcmp(flagstab.tab[i].flagname,"-mime")==0){
                    Listfile=flagmime(flagstab.tab[i].flagvalue,adresselist);
                }else if(strcmp(flagstab.tab[i].flagname,"-ctc")==0){
                    Listfile=flagctc(flagstab.tab[i].flagvalue,adresselist);
                }else if(strcmp(flagstab.tab[i].flagname,"-dir")==0){
                    dir_mode=true;
                    if (flagstab.tab[i].flagvalue!=NULL){
                        Listfile=flagdir(adresselist,flagstab.tab[i].flagvalue);
                    }else{
                        Listfile=flagdir(adresselist,NULL);
                    }
                }else if(strcmp(flagstab.tab[i].flagname,"-perm")==0){
                    Listfile=flagperm(flagstab.tab[i].flagvalue,adresselist);
                }else if(strcmp(flagstab.tab[i].flagname,"-test")==0){
                    printtabflags(flagstab);
                    exit(1);
                }
                while(Listfile->next!=NULL){
                    if (!isfileinlist(listfile2,Listfile->next->path)){
                        addfile(listfile2,Listfile->next->path);
                        
                    }
                    Listfile=Listfile->next;
                }
                
            }
        }
        
        return listfile2;
    }
}

//flag -size

listfile* flagsize(char* size, listfile* listoffile){
    char* root=listoffile->path;
    listfile* adresselist=listoffile;
    listfile* listfile2 = malloc(sizeof(listfile)*10);
    listfile2->path=listoffile->path;
    listfile2->next=NULL;
    while(listoffile!=NULL){
        listoffile=flagsizerec(listoffile,listfile2,size);
    }
    if(!or_mode){
        
        deleteListFile(adresselist->next,root);
        free(adresselist);
    }
    return listfile2;
}

listfile* flagsizerec(listfile* listoffile, listfile* listfile2,char* size){
    if ((is_regular_file(listoffile->path) && dir_mode == false)||(dir_mode == true && is_directory(listoffile->path))){
            if(testsize(size,listoffile->path)){
                addfile(listfile2,listoffile->path);
            }
    }
    return listoffile->next;
}

//flag -name

listfile* flagname(char* name, listfile* listoffile){
    char* root=listoffile->path;
    listfile* adresselist=listoffile;
    listfile* listfile2 = malloc(sizeof(listfile)*10);
    listfile2->path=listoffile->path;
    listfile2->next=NULL;
    while(listoffile!=NULL){
        listoffile=flagnamerec(listoffile,listfile2,name);
    }
    if(!or_mode){
        deleteListFile(adresselist->next,root);
        free(adresselist);
    }
    return listfile2;
}

listfile* flagnamerec(listfile* listoffile, listfile* listfile2,char* name){
    if ((is_regular_file(listoffile->path) && dir_mode == false)||(dir_mode == true && is_directory(listoffile->path))){
            if(testname(name,listoffile->path)){
                addfile(listfile2,listoffile->path);
            }
        }
    return listoffile->next;
}

//flag -date

listfile* flagdate(char* date, listfile* listoffile){
    char* root=listoffile->path;
    listfile* adresselist=listoffile;
    listfile* listfile2 = malloc(sizeof(listfile)*10);
    listfile2->path=listoffile->path;
    listfile2->next=NULL;
    while(listoffile!=NULL){
        listoffile=flagdaterec(listoffile,listfile2,date);
    }
    if(!or_mode){
        
        deleteListFile(adresselist->next,root);
        free(adresselist);
    }
    return listfile2;
}

listfile* flagdaterec(listfile* listoffile,listfile* listfile2,char* date){
    if ((is_regular_file(listoffile->path) && dir_mode == false)||(dir_mode == true && is_directory(listoffile->path))){
            if(testdate(listoffile->path,date)){
                addfile(listfile2,listoffile->path);
            }
        }
    return listoffile->next;
}

//flag -mime

listfile* flagmime(char* mime, listfile* listoffile){
    char* root=listoffile->path;
    listfile* adresselist=listoffile;
    listfile* listfile2 = malloc(sizeof(listfile)*10);
    listfile2->path=listoffile->path;
    listfile2->next=NULL;
    while(listoffile!=NULL){
        listoffile=flagmimerec(listoffile,listfile2,mime);
    }
    if(!or_mode){
        
        deleteListFile(adresselist->next,root);
        free(adresselist);
    }
    return listfile2;
}

listfile* flagmimerec(listfile* listoffile,listfile* listfile2,char* mime){
    if ((is_regular_file(listoffile->path) && dir_mode == false)||(dir_mode == true && is_directory(listoffile->path))){
            if(testmime(listoffile->path,mime)){
                addfile(listfile2,listoffile->path);
            }
        }
    return listoffile->next;
}

//flag -perm

listfile* flagperm(char* perm, listfile* listoffile){
    char* root=listoffile->path;
    listfile* adresselist=listoffile;
    listfile* listfile2 = malloc(sizeof(listfile)*10);
    listfile2->path=listoffile->path;
    listfile2->next=NULL;
    while(listoffile!=NULL){
        listoffile=flagpermrec(listoffile,listfile2,perm);
    }
    if(!or_mode){
        
        deleteListFile(adresselist->next,root);
        free(adresselist);
    }
    return listfile2;
}

listfile* flagpermrec(listfile* listoffile,listfile* listfile2,char* perm){
    if ((is_regular_file(listoffile->path) && dir_mode == false)||(dir_mode == true && is_directory(listoffile->path))){
            if(testperm(listoffile->path,perm)){
                addfile(listfile2,listoffile->path);
            }
        }
    return listoffile->next;
}

//flag -dir

listfile* flagdir(listfile* listoffile,char* name){
    char* root=listoffile->path;
    listfile* adresselist=listoffile;
    listfile* listfile2 = malloc(sizeof(listfile)*10);
    listfile2->path=listoffile->path;
    listfile2->next=NULL;
    while(listoffile!=NULL){
        listoffile=flagdirrec(listoffile,listfile2,name);
    }
    if(!or_mode){
        
        deleteListFile(adresselist->next,root);
        free(adresselist);
    }
    return listfile2;
}

listfile* flagdirrec(listfile* listoffile,listfile* listfile2,char* name){
    if(name == NULL){
            if (is_directory(listoffile->path)){
                addfile(listfile2,listoffile->path);
            }
        }else{if (is_directory(listoffile->path) && strcmp(basename(listoffile->path),name)==0){
            addfile(listfile2,listoffile->path);
        }
        }
    return listoffile->next;
}

//flag -ctc

listfile* flagctc(char* name, listfile* listoffile){
    char* root=listoffile->path;
    listfile* adresselist=listoffile;
    listfile* listfile2 = malloc(sizeof(listfile)*10);
    listfile2->path=listoffile->path;
    listfile2->next=NULL;
    while(listoffile!=NULL){
        listoffile=flagctcrec(listoffile,listfile2,name);
    }
    if(!or_mode){
        
        deleteListFile(adresselist->next,root);
        free(adresselist);
    }
    return listfile2;
}

listfile* flagctcrec(listfile* listoffile,listfile* listfile2,char* name){
     if (is_regular_file(listoffile->path)){
            if(testctc(listoffile->path,name)){
                addfile(listfile2,listoffile->path);
            }
    }
    return listoffile->next;
}
