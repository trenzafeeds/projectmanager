/********************
 * settings_struct.h
 ********************/

#ifndef SETTINGS_STRUCT
#define SETTINGS_STRUCT

typedef struct _conf *conf;
struct _conf {
  int git;
  int git_readme;
  int git_ignore;
  int git_commit;
};
#define CONF_SIZE sizeof(struct _conf)

#endif /* SETTINGS_STRUCT */
