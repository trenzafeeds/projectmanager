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

conf load_config(FILE *conf_file)
{
  conf config_struct = conf_struct();
  read_bytes(config_struct, CONF_SIZE, 1, conf_file);
  return config_struct;
}

int mode_exists(FILE *rawconf, char *mode_name)
{
  return 0;
}

// dpath empty pointer for directory path
// allocate to strlen(fpath) + 1
int extract_dir(char *fpath, char *dpath)
{
  char *dptr;
  strcpy(dpath, fpath);
  dptr = strrchr(dpath, '/');
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
    print_error("");
  return fptr;
}

int read_bytes(void *mem, size_t size, size_t num, FILE *conf_file)
{
  int rc;
  if ((rc = fread(mem, size, num, conf_file)) == 0)
    app_error("Could not struct correctly from config file.", 1);
  return rc;
}

int compile_regex(regex_t robject, char *pattern, int flags)
{
  if (regcomp(&robject, pattern, flags) != 0)
    app_error("Error: Regex compilation failed.", 1);
  else
    return 0;
}

int regex_fmatch(FILE *infile, char *pattern, int rflags)
{
  return 0;
}

void print_error(char *msg)
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
