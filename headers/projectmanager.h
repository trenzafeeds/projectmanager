/****************************
 * projectmanager.h
 * 
 * Master header for a basic
 * suite of organizational/
 * administrative tools.
 * 
 * Kat Cannon-MacMartin
 * Marlboro College
 * guthrie@marlboro.edu
 ****************************/

/* Standards */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <regex.h>

/* Local libaries */
#include "utils.h"

/* Define for debugging */
// #define DEBUG

/* Define filepaths */
#define PM_PATH "/usr/local/lib/projectmanager/"
#define ICONF_SPATH ".tmp/iconf"
// #define CONF_PATH

#ifndef PMHEADER
#define PMHEADER

#define TRUE 1
#define FALSE 0

#endif /* PMHEADER */
