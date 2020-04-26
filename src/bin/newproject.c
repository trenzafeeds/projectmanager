/***********************
 * newproject.c
 * 
 * Kat Cannon-MacMartin
 * Marlboro College
 * guthrie@marlboro.edu
 ***********************/

#include "newproject.h"

int mode_exists(char *name)
{
  char mode_path[100];
  strcpy(mode_path, PM_PATH TMP);
  strcat(mode_path, name);
  strcat(mode_path, ".mode");
  return file_exists(mode_path);
}

int main(int argc, char** argv)
{
  if (argc < 3)
    app_error("Error: not enough arguments.", 1);
  
  int dirlen = strlen(argv[2]);
  char dir[dirlen + 1];
  char name[dirlen + 1];
  int rc;
  
  if ((rc = get_dir(argv[2], dir, name)) == 0) {
    app_error("Error reading newproject arguments.", 1);
  } else {
    if (rc == 1)
      dir[0] = '\0';
  }

  if (!(mode_exists(argv[1]))) {
    printf("Error: mode %s does not exist.\n", argv[1]);
    app_error("Perhaps you need to run `pm -c` to update config?", 1);
  }

  FILE *iconf = open_file(PM_PATH ICONF_SPATH, "r");
  conf config = conf_struct();
  load_config(iconf, config);

  free(config);
  fclose(iconf);

  return 0;
}
