/*****************
 * print_config.c
 *****************/

#include "tests.h"

int main()
{
  FILE *iconf = open_file(PM_PATH ICONF_SPATH, "r");
  conf config = load_config(iconf);
  printf("git: %d\n", config->git);
  free(config);
  fclose(iconf);
}
