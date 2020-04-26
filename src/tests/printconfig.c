/*****************
 * print_config.c
 *****************/

#include "tests.h"

int main()
{
  FILE *iconf = open_file(PM_PATH ICONF_SPATH, "r");
  conf config = conf_struct();
  load_config(iconf, config);
  printf("git: %d\n", config->git);
  printf("git_readme: %d\n", config->git_readme);
  printf("git_ignore: %d\n", config->git_ignore);
  printf("git_commit: %d\n", config->git_commit);
  printf("mode_count: %d\n", config->mode_count);
  for (int i = 0; i < config->mode_count; i++) {
    printf("%s\n", config->modes[i]);
    fflush(stdout);
  }
  free(config);
  fclose(iconf);
}
