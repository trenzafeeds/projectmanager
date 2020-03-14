/***********************
 * utils.c
 *
 * Kat Cannon-MacMartin
 * Marlboro College
 * guthrie@marlboro.edu
 ***********************/

#include 'projectmanager.h'

void print_errno(char *msg)
{
  fprintf(stdout, "%s: %s\n", strerror(errno), msg);
  exit(1);
}

void app_error(char *msg, int exit)
{
  fprintf(stdout, "%s\n", msg);
  if (exit)
    exit(1);
  return;
}

FILE *open_file(char *fpath, char *action)
{
  FILE *fptr;
  if ((fptr = fopen(fpath, action)) == NULL)
    print_errno("");
  return fptr;
}

conf load_config(char *cpath)
{
}
