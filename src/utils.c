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

conf load_config(char *cpath)
{
  FILE *rawconf = open_file(cpath, "r");
}

FILE *open_file(char *fpath, char *action)
{
  FILE *fptr;
  if ((fptr = fopen(fpath, action)) == NULL)
    print_errno("");
  return fptr;
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
