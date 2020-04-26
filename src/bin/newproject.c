/***********************
 * newproject.c
 * 
 * Kat Cannon-MacMartin
 * Marlboro College
 * guthrie@marlboro.edu
 ***********************/

#include "newproject.h"

int main(int argc, char** argv)
{
  if (argc < 3)
    app_error("Error: not enough arguments.", 1);
  
  int dirlen = strlen(argv[3]);
  char dir[dirlen + 1];
  char name[dirlen + 1];
  int rc;
  
  if ((rc = get_dir(argv[3], dir, name)) == 0) {
    app_error("Error reading newproject arguments.", 1);
  } else {
    if (rc == 1)
      dir = NULL;
  }

  FILE *iconf = open_file(PM_PATH ICONF_SPATH, "r");
  conf config = conf_struct();
  load_config(iconf, config);

  free(config);
  fclose(iconf);

  return 0;
}
