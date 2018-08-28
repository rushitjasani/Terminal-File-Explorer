#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

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
        split_command();
        function_call();
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

void split_command(){
  string tmp="";
  for(unsigned int i=0;i<=command_string.size();i++){
    if(command_string[i] == ' ' ){
        my_command.push_back(tmp);
        tmp="";
    }
    else tmp+=command_string[i];
  }
  my_command.push_back(tmp);
  return;
}

void function_call(){
  string s=my_command[0];
  if(s == "copy"){
    cout << s ;
  }
  else if(s == "move"){
    cout << s ;
  }
  else if(s == "rename"){
    cout << s ;
  }
  else if(s == "create_file"){
    cout << s ;
  }
  else if(s == "create_dir"){
    cout << s ;
  }
  else if(s == "delete_file"){
    cout << s ;
  }
  else if(s == "delete_dir"){
    cout << s ;
  }
  else if(s == "goto"){
    cout << s ;
  }
  else if(s == "search"){
    cout << s ;
  }
  else if(s == "snapshot"){
    cout << s ;
  }
  else{
    cout << "THULLU" ;
  }

}
