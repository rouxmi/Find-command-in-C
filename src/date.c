#include "../includes/date.h"

bool testdate(char* file, char* inputDuration){
    bool inv = false;
    int difference = get_last_modification(file);
    char *temps;
    if (strcmp(inputDuration, "now") == 0) {
        temps = malloc(strlen("0m")+1);
        strcpy(temps, "0m");
    } else if (strcmp(inputDuration, "today") == 0) {
        temps = malloc(strlen("1j")+1);
        strcpy(temps, "1j");
    } else if (strcmp(inputDuration, "yesterday") == 0) {
        temps = malloc(strlen("2j")+1);
        strcpy(temps, "2j");
    } else if (strcmp(inputDuration, "this week") == 0) {
        temps = malloc(strlen("7j")+1);
        strcpy(temps, "7j");
    } else if (strcmp(inputDuration, "this month") == 0) {
        temps = malloc(strlen("30j")+1);
        strcpy(temps, "30j");
    } else if (strcmp(inputDuration, "this year") == 0) {
        temps = malloc(strlen("365j")+1);
        strcpy(temps, "365j");
    } else
    if (inputDuration[0] == '+') {
        temps = malloc(strlen(inputDuration));
        strcpy(temps, inputDuration+1);
        inv = true;
    } else if (inputDuration[0] == '-') {
        temps = malloc(strlen(inputDuration));
        strcpy(temps, inputDuration+1);
    } else {
        temps = malloc(strlen(inputDuration));
        strcpy(temps, inputDuration);
    }

    int days = 0, hours = 0, minutes = 0;
    for (int i = 0; i < strlen(temps); i++) {
        if (temps[i] == 'j') {
            sscanf(temps, "%dj", &days);
        } else if (temps[i] == 'h') {
            sscanf(temps, "%dh", &hours);
        } else if (temps[i] == 'm') {
            sscanf(temps, "%dm", &minutes);
        }
    }

    free(temps);
//    printf("days: %d, hours: %d, minutes: %d \n", days, hours, minutes);
    int duration = days*24*60*60 + hours*60*60 + minutes*60;
    if (!inv){
        if (difference < duration){
            return true;
        } else {
            return false;
        }
    }else{
        if (difference > duration){
            return true;
        } else {
            return false;
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
