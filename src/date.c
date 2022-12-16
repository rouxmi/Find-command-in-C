#include "../includes/date.h"

bool testdate(char* file, char* inputDuration){
    struct stat file_info;
    bool inv = false;
    int status = stat(file, &file_info);
    if (status != 0) {
        printf("Error: %s\n", strerror(errno));
        exit(1);
    }
    char *temps;
    if (inputDuration[0] != '+'){
        temps= inputDuration;
    }
    else{
        temps = malloc(strlen(inputDuration));
        strcpy(temps, inputDuration+1);
        inv = true;
    }
    time_t modificationDate = file_info.st_mtime;
    time_t currentDate = time(NULL);
    time_t difference = currentDate - modificationDate;
    int minutes, hours, days;
    minutes = hours = days = 0;
    sscanf(temps, "%dm%dh%dj", &minutes, &hours, &days);
    free(temps);
    printf("days: %d, hours: %d, minutes: %d \n", days, hours, minutes);
    int duration = days*24*60*60 + hours*60*60 + minutes*60;
    if (!inv){
        if (difference < duration){
            printf("File %s is older than %d %ld\n", file, duration,difference);
            return true;
        } else {
            return false;
        }
    }else{
        if (difference < duration){
            return false;
        } else {
            return true;
        }
    }
}
