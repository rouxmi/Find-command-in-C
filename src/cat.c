#include "../includes/cat.h"

bool testctc(char* file_path,char* str) {
  // Open the file
  FILE* file = fopen(file_path, "r");

  // Check if the file was successfully opened
  if (file == NULL) {
    return false;
  }

  // Read the file line by line
  char line[1024];
  while (fgets(line, sizeof(line), file) != NULL) {
    // Check if the string is present in the current line
    if (strstr(line, str) != NULL) {
      // Close the file and return 1 if the string is found
      fclose(file);
      return true;
    }
  }

  // Close the file and return 0 if the string is not found
  fclose(file);
  return false;
}