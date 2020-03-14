/***********************
 * pm.c
 *
 * Kat Cannon-MacMartin
 * Marlboro College
 * guthrie@marlboro.edu
 ***********************/

#include 'pm.h'

int main(int argc, char* argv[])
{
  if (argc == 1){
    fprintf(stdout, "%s\n", MAN);
    exit(0);
  }

  switch(argv[1]){
  case "-c":
  case "--config":
    break;
  }
}
