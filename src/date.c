#include "../includes/date.h"

bool testdate(char* file, char* inputDuration){
    bool inv = false;
    int difference = get_last_modification(file);
    char *temps;
    if (inputDuration[0] != '+' && inputDuration[0] != '-'){
        temps= inputDuration;
    }
    else{
        temps = malloc(strlen(inputDuration));
        strcpy(temps, inputDuration+1);
        if (inputDuration[0] != '-'){
            inv = true;
        }
    }
    int minutes, hours, days;
    minutes = hours = days = 0;
    sscanf(temps, "%dm%dh%dj", &minutes, &hours, &days);
    free(temps);
    printf("days: %d, hours: %d, minutes: %d \n", days, hours, minutes);
    int duration = days*24*60*60 + hours*60*60 + minutes*60;
    if (!inv){
        if (difference < duration){
            return true;
        } else {
            return false;
        }
    }else{
        if (difference > duration){
            return false;
        } else {
            return true;
        }
    }
}

double get_last_modification(const char *file_path) {
    struct stat st;
    char *cp_path;

    cp_path = (char *)malloc(sizeof(char) * (strlen(file_path) + 1));
    strcpy(cp_path, file_path);

    if (stat(cp_path, &st) == 0)
    {
        time_t t = st.st_mtime;
        time_t now = time(NULL);

        // Free memory
        free(cp_path);

        return difftime(now, t);
    }
    else
    {
        // Free memory
        free(cp_path);

        return -1;
    }
}
