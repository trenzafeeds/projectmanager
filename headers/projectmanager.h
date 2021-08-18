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

/* String macros */
#define STR(x) #x
#define XSTR(x) STR(x)

/* Check if path to working directory defined by Makefile, 
 * then stringize it 
 */
#ifndef WORK_DIR
#error "Path to local directory not defined. Read Makefile for information."
#endif

#define PM_PATH XSTR(WORK_DIR)

/* Define for debugging */
// #define DEBUG

/* Define filepaths */
#define ICONF_SPATH ".tmp/iconf"
#define TMP ".tmp/"
// #define CONF_PATH

#ifndef PMHEADER
#define PMHEADER

#define TRUE 1
#define FALSE 0

#endif /* PMHEADER */
