#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

bool goto_flag;
void command_mode(){
  while(1){
    goto_flag = false;
    cx = terminal.ws_row;
    cy = 1;
    CURSER;
    printf("\x1b[0K");
    printf(":");
    cy++;
    char ch;
    command_string.clear();
    my_command.clear();
    while(1){
      ch = cin.get();
      if(ch == 27){
        cx = 1;
        cy = 1;
        CURSER;
        return;
      }
      else if(ch == 10){
        command_string.push_back(' ');
        split_command();
        function_call();
        if(goto_flag) return;
        break;
      }
      else if(ch == 127){
        if(cy>2){
          cy--;
          CURSER;
          printf("\x1b[0K");
          command_string.pop_back();
        }
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

void show_error(){
  cx = terminal.ws_row;
  cy = 1;
  CURSER;
  printf("\x1b[0K");
  printf("Something went wrong. Try again.");
  return;
}
void show_success(){
  cx = terminal.ws_row;
  cy = 1;
  CURSER;
  printf("\x1b[0K");
  printf("Done :)");
  return;
}

void my_goto(){
  if(my_command.size() != 2) printf("Improper Arguments.");
  else{
    string goto_path = create_absolute_path(my_command[1]);
    strcpy(cur_dir,goto_path.c_str());
    goto_flag = true;
  }
  return;
}
void my_search(){}

/*============================================================
take relative path and convert to absolute path.
=============================================================*/
string create_absolute_path(string r_path){
  string abs_path="";
  if(r_path[0] == '~'){
    r_path = r_path.substr(1,r_path.length());
    abs_path = string(root) + r_path;
  }
  else if(r_path[0] == '/'){
    abs_path = string(root) + r_path;
  }
  else if(r_path[0] == '.' && r_path[1] == '/' ){
    abs_path = string(cur_dir) + r_path.substr(1,r_path.length());
  }
  else{
    abs_path = string(cur_dir)+"/"+r_path;
  }
  return abs_path;
}
/*============================================================
take command string, split it and put it in string vector.
=============================================================*/
void split_command(){
  string tmp="";
  unsigned int i=0;
  for(;i<=command_string.size();i++){
    if(command_string[i] == ' ' ){
      my_command.push_back(tmp);
      tmp = "";
    }
    else tmp+=command_string[i];
  }
  return;
}
/*============================================================
calls various functions based on first argument of command.
=============================================================*/
void function_call(){
  string s=my_command[0];
  if(s == "copy")             my_copy();
  else if(s == "move")        my_move();
  else if(s == "rename")      my_rename();
  else if(s == "create_file") create_file();
  else if(s == "create_dir")  create_dir();
  else if(s == "delete_file") delete_file();
  else if(s == "delete_dir")  delete_dir();
  else if(s == "goto")        my_goto();
  else if(s == "search")      my_search();
  else if(s == "snapshot")    snapshot();
  else{
    cout << "INVALID COMMAND :: try again";
    sleep(3);
  }
  return;
}
