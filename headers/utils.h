
/***********************
 * utils.h
 *
 * Kat Cannon-MacMartin
 * Marlboro College
 * guthrie@marlboro.edu
 ***********************/

//Included in : projectmanager.h

#include "settings_struct.h"

#ifndef UTILS_HEADER
#define UTILS_HEADER

conf conf_struct();
FILE *open_config(char *custom_path, char *action);
int load_config(FILE *rawconf, conf struct_ptr);

int extract_dir(char *fpath, char *dpath, char *fname);
int get_dir(char *path, char *pdir, char *pname);
int file_exists(char *fname);
FILE *open_file(char *fpath, char *action);
int read_bytes(void *mem, size_t size, size_t num, FILE *conf_file);

int compile_regex(regex_t robject, char *pattern, int flags);
int regex_fmatch(FILE *infile, char *pattern, int rflags);

int strcut(char *src, char *dest, int begin, int len);

void print_error(char *msg);
void app_error(char *msg, int exit_code);

#endif /* UTILS_HEADER */
