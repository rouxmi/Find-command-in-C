#include "../includes/date.h"

/* tm_duration stringToDuration(char* inputDuration){
    tm_duration duration;
    sscanf(inputDuration, "%dj%dh%dm", &duration.days, &duration.hours, &duration.minutes);
    return duration;
}
 */

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
    int seconds, hours, days;
    sscanf(inputDuration, "%dj%dh%dm", &days, &hours, &seconds);
    int duration = days*24*60*60 + hours*60*60 + seconds*60;
    if (duration < difference){
        return true;
    }
    return false;
}
