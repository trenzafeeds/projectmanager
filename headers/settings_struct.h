/********************
 * settings_struct.h
 ********************/

#ifndef SETTINGS_STRUCT
#define SETTINGS_STRUCT

#define MAXMODES 20
#define MODENAMELEN 15

typedef struct _conf *conf;
struct _conf {
  int git;
  int git_readme;
  int git_ignore;
  int git_commit;
  char modes[MAXMODES][MODENAMELEN];
};
#define CONF_SIZE sizeof(struct _conf)

#endif /* SETTINGS_STRUCT */
