#include "../includes/util.h"


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


tabflag getflag(int mainargc,char *mainargv[ ]){
    tabflag tab;
    tab.size=0;
    tab.tab=malloc(sizeof(flag));
    for (int i = 2; i < mainargc; i = i+2) {
        if ( strcmp(mainargv[i], "-name") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-name";
            tab.tab[tab.size].flagvalue=mainargv[i+1];
            tab.size++;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        } else if ( strcmp(mainargv[i], "-size") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-size";
            tab.tab[tab.size].flagvalue=mainargv[i+1];
            tab.size++;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        } else if ( strcmp(mainargv[i], "-date") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-date";
            tab.tab[tab.size].flagvalue=mainargv[i+1];
            tab.size++;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        } else if ( strcmp(mainargv[i], "-mime") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-mime";
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
            tab.tab[tab.size].flagvalue=mainargv[i+1];
            tab.size++;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        }else if ( strcmp(mainargv[i], "-threads") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-threads";
            tab.tab[tab.size].flagvalue=mainargv[i+1];
            tab.size++;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        }else if ( strcmp(mainargv[i], "-dir" ) == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-dir";
            tab.tab[tab.size].flagvalue=NULL;
            tab.size++;
            i--;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        } else if ( strcmp(mainargv[i], "-test") == 0 ) {
            tab.tab[tab.size].isflag=true;
            tab.tab[tab.size].flagname="-test";
            tab.tab[tab.size].flagvalue=NULL;
            tab.size++;
            i--;
            tab.tab=realloc(tab.tab,(tab.size+1)*sizeof(flag));
        } else {    
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


void addfile(listfile* listfile,char* path){
    while(listfile->next!=NULL){
        listfile=listfile->next;
    }
    listfile->next=malloc(sizeof(listfile)*2);
    listfile->next->path=malloc(strlen(path)+1);
    strcpy(listfile->next->path,path);
    listfile->next->next=NULL;
}


listfile* getlastfile(listfile* listfile){
    while(listfile->next!=NULL){
        listfile=listfile->next;
    }
    return listfile;
}


void printlistfile(listfile* listfile){
    while(listfile!=NULL){
        if (strcmp(listfile->path,"end")!=0){
            printf("%s\n",listfile->path);
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

//call the function depending on the flag
listfile* callflag(tabflag flagstab, listfile* listfile){
    for(int i=0; i<flagstab.size;i++){
        if(flagstab.tab[i].isflag){
            if(strcmp(flagstab.tab[i].flagname,"-name")==0){
                listfile=flagname(flagstab.tab[i].flagvalue,listfile);
            }else if(strcmp(flagstab.tab[i].flagname,"-size")==0){
                listfile=flagsize(flagstab.tab[i].flagvalue,listfile);
            }else if(strcmp(flagstab.tab[i].flagname,"-date")==0){
                listfile=flagdate(flagstab.tab[i].flagvalue,listfile);
            }else if(strcmp(flagstab.tab[i].flagname,"-mime")==0){
                listfile=flagmime(flagstab.tab[i].flagvalue,listfile);
            }else if(strcmp(flagstab.tab[i].flagname,"-ctc")==0){
                //listfile=flagctc(flagstab.tab[i].flagvalue,listfile);
            }else if(strcmp(flagstab.tab[i].flagname,"-dir")==0){
                listfile=flagdir(listfile);
            }else if(strcmp(flagstab.tab[i].flagname,"-perm")==0){
                listfile=flagperm(flagstab.tab[i].flagvalue,listfile);
            }else if(strcmp(flagstab.tab[i].flagname,"-test")==0){
                printtabflags(flagstab);
                exit(1);
            }
        }
    }
    return listfile;
}

//flag -size

listfile* flagsize(char* size, listfile* listoffile){
    char* root=listoffile->path;
    listfile* adresselist=listoffile;
    listfile* listfile2 = malloc(sizeof(listfile)*10);
    listfile2->path=listoffile->path;
    listfile2->next=NULL;
    while(listoffile!=NULL){
        if (is_regular_file(listoffile->path)){
            if(testsize(size,listoffile->path)){
                addfile(listfile2,listoffile->path);
            }
        }
        listoffile=listoffile->next;
    }
    deleteListFile(adresselist->next,root);
    free(adresselist);
    return listfile2;
}

//flag -name

listfile* flagname(char* name, listfile* listoffile){
    char* root=listoffile->path;
    listfile* adresselist=listoffile;
    listfile* listfile2 = malloc(sizeof(listfile)*10);
    listfile2->path=listoffile->path;
    listfile2->next=NULL;
    while(listoffile!=NULL){
        if (is_regular_file(listoffile->path)){
            if(testname(name,listoffile->path)){
                addfile(listfile2,listoffile->path);
            }
        }
        listoffile=listoffile->next;
    }
    deleteListFile(adresselist->next,root);
    free(adresselist);
    return listfile2;
}

//flag -date

listfile* flagdate(char* date, listfile* listoffile){
    char* root=listoffile->path;
    listfile* adresselist=listoffile;
    listfile* listfile2 = malloc(sizeof(listfile)*10);
    listfile2->path=listoffile->path;
    listfile2->next=NULL;
    while(listoffile!=NULL){
        if (is_regular_file(listoffile->path)){
            if(testdate(listoffile->path,date)){
                addfile(listfile2,listoffile->path);
            }
        }
        listoffile=listoffile->next;
    }
    deleteListFile(adresselist->next,root);
    free(adresselist);
    return listfile2;
}

//flag -mime

listfile* flagmime(char* mime, listfile* listoffile){
    char* root=listoffile->path;
    listfile* adresselist=listoffile;
    listfile* listfile2 = malloc(sizeof(listfile)*10);
    listfile2->path=listoffile->path;
    listfile2->next=NULL;
    while(listoffile!=NULL){
        if (is_regular_file(listoffile->path)){
            if(testmime(listoffile->path,mime)){
                addfile(listfile2,listoffile->path);
            }
        }
        listoffile=listoffile->next;
    }
    deleteListFile(adresselist->next,root);
    free(adresselist);
    return listfile2;
}

//flag -perm

listfile* flagperm(char* perm, listfile* listoffile){
    char* root=listoffile->path;
    listfile* adresselist=listoffile;
    listfile* listfile2 = malloc(sizeof(listfile)*10);
    listfile2->path=listoffile->path;
    listfile2->next=NULL;
    while(listoffile!=NULL){
        if (is_regular_file(listoffile->path)){
            if(testperm(listoffile->path,perm)){
                addfile(listfile2,listoffile->path);
            }
        }
        listoffile=listoffile->next;
    }
    deleteListFile(adresselist->next,root);
    free(adresselist);
    return listfile2;
}

//flag -dir

listfile* flagdir(listfile* listoffile){
    char* root=listoffile->path;
    listfile* adresselist=listoffile;
    listfile* listfile2 = malloc(sizeof(listfile)*10);
    listfile2->path=listoffile->path;
    listfile2->next=NULL;
    while(listoffile!=NULL){
        if (is_directory(listoffile->path)){
            addfile(listfile2,listoffile->path);
        }
        listoffile=listoffile->next;
    }
    deleteListFile(adresselist->next,root);
    free(adresselist);
    return listfile2;
}