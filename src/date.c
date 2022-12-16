#include "../includes/date.h"

bool duration(char* file, char* inputDuration){
    struct stat file_info;
    int status = stat(file, &file_info);
    if (status != 0) {
        printf("Error: %s\n", strerror(errno));
        exit(1);
    }
    time_t modificationDate = file_info.st_mtime;
    time_t currentDate = time(NULL);
    time_t difference = currentDate - modificationDate;
    int minutes, hours, days;
    sscanf(inputDuration, "%dj%dh%dm", &days, &hours, &minutes);
    int duration = days*24*60*60 + hours*60*60 + minutes*60;
    if (duration < difference){
        return false;
    } else {
        return true;
    }
}
