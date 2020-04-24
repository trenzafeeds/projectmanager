
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
conf load_config(FILE *rawconf);

int mode_exists(FILE *rawconf, char *mode_name);

int extract_dir(char *fpath, char *dpath);
FILE *open_file(char *fpath, char *action);
int read_bytes(void *mem, size_t size, size_t num, FILE *conf_file);

int compile_regex(regex_t robject, char *pattern, int flags);
int regex_fmatch(FILE *infile, char *pattern, int rflags);

void print_error(char *msg);
void app_error(char *msg, int exit_code);

#endif /* UTILS_HEADER */
