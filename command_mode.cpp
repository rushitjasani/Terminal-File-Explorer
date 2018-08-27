#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

void call_function(){
  string s = "touch rushit.txt";
  system(s.c_str());
  return;
}

void command_mode(){
  while(1){
    cx = terminal.ws_row;
    cy = 0;
    CURSER;
    printf("\x1b[0K");
    printf(":");
    char ch;
    command_string.clear();
    while(1){
      ch = cin.get();
      if(ch == 27){
        cx = 1;
        cy = 0;
        CURSER;
        return;
      }
      else if(ch == 10){
        call_function();
        break;
      }
      else{
        cout << ch;
        cy++;
        command_string.push_back(ch);
      }
    }
  }
  return;
}
