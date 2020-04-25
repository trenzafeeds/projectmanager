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
  if (argcnt < 3) // It's a little heart! :)
    return NULL; // Add custom error message and/or use pm to print man
  else {
    char pdir[strlen(argvars[2]) + 1];
    if (extract_dir(argvars[2], pdir)) {
      struct stat s;
      if (!(stat(pdir, &s) == 0 && S_ISDIR(s.st_mode)))
	app_error("Error: invalid directory path.", 1);
    }
  }
  return NULL; // Must actually return opened config file
}

int main(int argc, char** argv)
{
  FILE *iconf;
  if ((iconf = test_args(argc, argv)) == NULL)
    app_error("Error reading newproject arguments.", 1);

  return 0;
}
