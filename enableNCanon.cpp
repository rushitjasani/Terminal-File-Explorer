#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

struct termios raw, newraw;

void disableNCanon(){
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);
}

void enableNCanon(){
  //getting the initial terminal settings
  tcgetattr(STDIN_FILENO, &raw);
  atexit(disableNCanon);
  newraw = raw;

  //changing ICANON for entering Non Canonical mode.
  newraw.c_lflag &= ~ICANON;
  newraw.c_lflag &= ~ECHO;

  //set new terminal settings.
  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) != 0) {
    fprintf(stderr,"Could not set attributes\n");
  }
  else{
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
      if (iscntrl(c)) {
        printf("%d\n", c);
      } else {
        printf("%d ('%c')\n", c, c);
      }
    }
  }
  exit(0);
}
