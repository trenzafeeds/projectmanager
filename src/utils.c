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

int load_config(FILE *conf_file, conf struct_ptr)
{
  return read_bytes(struct_ptr, CONF_SIZE, 1, conf_file);
}

// dpath empty buffer for directory path
// allocate to strlen(fpath) + 1
// fname empty buffer for new name (after path)
int extract_dir(char *fpath, char *dpath, char *fname)
{
  char *dptr;
  strcpy(dpath, fpath);
  dptr = strrchr(dpath, '/');
  if (dptr) {
    *dptr = '\0';
    strcut(fpath, fname, strlen(dpath) + 1, strlen(fpath));
    return TRUE;
  } else {
    strcpy(fname, fpath);
    dpath = NULL;
    return FALSE;
  }
}

// Returns number of buffers written to. So 0 if
// there is an error, 1 if only a name was supplied,
// and 2 if a directory path + name was supplied.
int get_dir(char *path, char *pdir, char *pname)
{
  if (extract_dir(path, pdir, pname)) {
    struct stat s;
    if (!(stat(pdir, &s) == 0 && S_ISDIR(s.st_mode))) {
      app_error("Error: invalid directory path.", 1);
    } else {
      return 2;
    }
  } else {
    return 1;
  }
  return 0;
}

int file_exists(char *fname)
{
  struct stat s;
  return (stat(fname, &s) == 0);
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

int strcut(char *src, char *dest, int begin, int end)
{
  if (strncpy(dest, src + begin, end - begin) == NULL)
    app_error("Error cutting string.", 1);
  dest[end - begin] = '\0';
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
