/***********************
 * newproject.c
 * 
 * Kat Cannon-MacMartin
 * Marlboro College
 * guthrie@marlboro.edu
 ***********************/

#include "newproject.h"

FILE *test_args(int argcnt, char** argvars)
{
  FILE *config;
  if (argcnt == 1)
    return NULL; // Add custom error message and/or use pm to print man
  if (argcnt > 3) {
    struct stat s;
    if (!(stat(argv[3], &s) == 0 && S_ISDIR(s.st_mode)))
      app_error("Error: Directory for location of new project does\
not exist.");
  }  
}

int main(int argc, char** argv)
{
  FILE *iconf;
  if ((iconf = test_args(argc, argv)) == NULL)
    app_error("Error reading newproject arguments.", 1);

  return 0;
}
