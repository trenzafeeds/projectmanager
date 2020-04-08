####
# Makefile for projectmanager C files
# Kat Cannon-MacMartin
# Adapted from a Makefile by Jim Mahoney
###

NEWPROJECT_T = bin/fn/newproject
NEWPROJECT_S = newproject.c utils.c

CFLAGS = -O2 -Wall -Iheaders

CC = gcc

###################################################

NEWPROJECT_O = $(NEWPROJECT_S:.c=.o)

all:
	make newproject
	make clean

newproject: $(NEWPROJECT_O)
	$(CC) $(CFLAGS) $(NEWPROJECT_O) -o $(NEWPROJECT_T)
	make clean

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o *.d
