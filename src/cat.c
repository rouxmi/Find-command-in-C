#include "../includes/cat.h"

bool testctc(char* file_path,char* str) {
  // Open the file
  FILE* file = fopen(file_path, "r");

  // Check if the file was successfully opened
  if (file == NULL) {
    return false;
  }

  // Read the file line by line
  char line[4096];
  while (fgets(line, sizeof(line), file) != NULL) {
    if (strstr(line, str) != NULL){
        fclose(file);
        return true;
    }
    else{
        regex_t regex;
        int return_value = regcomp(&regex,str,0);
        return_value = regexec(&regex, line, 0, NULL, 0);
        regfree(&regex);
        if(return_value == 0){
            fclose(file);
            return true;
        }
    }
  }


  fclose(file);
  return false;
}