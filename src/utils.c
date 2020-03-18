/***********************
 * utils.c
 *
 * Kat Cannon-MacMartin
 * Marlboro College
 * guthrie@marlboro.edu
 ***********************/

#include "projectmanager.h"

conf conf_struct()
{
  conf cptr;
  if ((cptr = malloc(CONF_SIZE)) == NULL)
    print_error("");
  return cptr;
}

FILE *open_config(char *custom_path, char *action) // Usually pass NULL
{
  FILE *config_file
  if (custom_path != NULL)
    app_error("Custom iconf path not supported at this time.");
  else
    config_file = open_file(PM_PATH ICONF_PATH, action);
  return config_file;
}

conf load_config(FILE *rawconf)
{
  return conf_struct();
}

int mode_exists(FILE *rawconf, char *mode_name)
{
}

// dpath empty pointer for directory path
// allocate to strlen(fpath) + 1
int extract_dir(char *fpath, char *dpath)
{
  char *dptr;
  strcpy(dpath, fpath);
  dptr = strrchr(sptr, "/");
  if (dptr) {
    *dptr = '\0';
    return TRUE;
  } else {
    return FALSE;
  }
}

FILE *open_file(char *fpath, char *action)
{
  FILE *fptr;
  if ((fptr = fopen(fpath, action)) == NULL)
    print_errno("");
  return fptr;
}

void compile_regex(regex_t robject, char *pattern, int flags)
{
  if (regcomp(&robject, pattern, flags) != 0)
    app_error("Error: Regex compilation failed.");
  else
    return;
}

int regex_fmatch(FILE *infile, char *pattern, int rflags)
{
}

void print_errno(char *msg)
{
  fprintf(stdout, "%s: %s\n", strerror(errno), msg);
  exit(1);
}

void app_error(char *msg, int exit_code)
{
  fprintf(stdout, "%s\n", msg);
  if (exit_code)
    exit(exit_code);
  return;
}
