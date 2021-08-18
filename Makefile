
####
# Makefile for projectmanager C files
# Kat Cannon-MacMartin
# Adapted from a Makefile by Jim Mahoney
###

# NEED CURRENT DIR
PM_DIR=$(shell pwd)

NEWPROJECT_T = bin/fn/newproject
NEWPROJECT_S = src/bin/newproject.c src/utils.c

PRINTCONFIG_T = bin/fn/printconfig
PRINTCONFIG_S = src/tests/printconfig.c src/utils.c

CFLAGS = -O2 -Wall -Iheaders -DWORK_DIR=$(PM_DIR)

CC = gcc

###################################################

NEWPROJECT_O = $(NEWPROJECT_S:.c=.o)
PRINTCONFIG_O = $(PRINTCONFIG_S:.c=.o)

all:
	echo ${PM_DIR}
	make projectmanager
	make tests

projectmanager:
	make newproject
	make clean

tests:
	make printconfig
	make clean

newproject: $(NEWPROJECT_O)
	$(CC) $(CFLAGS) $(NEWPROJECT_O) -o $(NEWPROJECT_T)

printconfig: $(PRINTCONFIG_O)
	$(CC) $(CFLAGS) $(PRINTCONFIG_O) -o $(PRINTCONFIG_T)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f src/*.o src/bin/*.o src/tests/*.o
