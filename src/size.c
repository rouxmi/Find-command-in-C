#include "../includes/size.h"

double convert_unit(int size,char unit){
    long double multi=1;
    if (unit <= '0' || unit >= '9') {
    // it is not a number
        if (unit=='k'){
            multi=1024;
        }
        if (unit=='M'){
            multi=1024*1024;
        }
        if (unit=='G'){
            multi=1024*1024*1024;
        }
    }
    return (multi*size);
}

bool testsize(char* size,char* path){
    char sign = size[0];
    char unit = size[strlen(size)-1];
    char plus = '+';
    char moins = '-';
    char number[1000];
    long double insh;
    struct stat st;
    
    if (strcmp(path,"end")==0){return false;}
    

    if (sign==plus || sign == moins){
        strcpy(number, size+1);
    }
    else {
        strcpy(number,size);
    }
    if (unit <= '0' || unit >= '9') {
        int fin =strlen(number)-1;
        number[fin] = '\0';
    }   
    stat(path, &st);
    sscanf(number, "%LF", &insh); 

    long double size_number= convert_unit(insh,unit);
    long double f_size = st.st_size;


    if (sign==moins){
        if (f_size < size_number){
            return true;
        }
    }
    else{
        if (sign==plus){
            if (f_size > size_number){
                return true;
            }
        }
        else{
            if (f_size == size_number){
                return true;
            }
        }
    }
    return false;
}
