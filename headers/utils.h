
/***********************
 * utils.h
 *
 * Kat Cannon-MacMartin
 * Marlboro College
 * guthrie@marlboro.edu
 ***********************/

typedef struct _conf *conf;
struct _conf {
  int var;
};
#define CONF_SIZE sizeof(struct _conf);

conf load_config(char *cpath); 
