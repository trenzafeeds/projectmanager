
/***********************
 * utils.h
 *
 * Kat Cannon-MacMartin
 * Marlboro College
 * guthrie@marlboro.edu
 ***********************/

//Included in : projectmanager.h

#ifndef UTILS_HEADER
#define UTILS_HEADER

typedef struct _conf *conf;
struct _conf {
  int git;
};
#define CONF_SIZE sizeof(struct _conf);

conf conf_struct();
conf load_config(char *cpath);

FILE *open_file(char *fpath, char *action);

void print_error(char *msg);
void app_error(char *msg, int exit);

#endif /* UTILS_HEADER */
