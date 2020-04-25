/*****************
 * print_config.c
 *****************/

#include "tests.h"

int main()
{
  FILE *iconf = open_file(PM_PATH ICONF_SPATH, "r");
  conf config = load_config(iconf);
  printf("git: %d\n", config->git);
  printf("git_readme: %d\n", config->git_readme);
  printf("git_ignore: %d\n", config->git_ignore);
  printf("git_commit: %d\n", config->git_commit);
  free(config);
  fclose(iconf);
}
