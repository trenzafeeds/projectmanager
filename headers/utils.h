
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

void print_error(char *msg);
void app_error(char *msg, int exit);

FILE *open_file(char *fpath, char *action);

conf load_config(char *cpath); 

#endif /* UTILS_HEADER */
