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
        command_string.push_back(' ');
        split_command();
        function_call();
        cy = 0;
        cx = 1;
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


void my_copy(){}
void my_move(){}
void my_rename(){}
void create_file(){}

void create_dir(){
  for(unsigned int i=1;i<my_command.size();i++){
    string path = my_command[i];
    mkdir(path.c_str(),);
  }
}

void delete_file(){}
void delete_dir(){}
void my_goto(){}
void my_search(){}
void snapshot(){}


/*============================================================
take command string, split it and put it in string vector and
convert in absolute path.
=============================================================*/
void split_command(){
  string tmp="";
  string abs_path="";
  unsigned int i=0;
  while(command_string[i] != ' '){
    tmp+=command_string[i];
    i++;
  }
  my_command.push_back(tmp);
  i++;
  tmp = "";
  for(;i<=command_string.size();i++){
    if(command_string[i] == ' ' ){
      if(tmp[0] == '~'){
        tmp = tmp.substr(1,tmp.length());
        abs_path = string(root) + tmp;
      }
      else if(tmp[0] == '/'){
        abs_path = string(root) + tmp;
      }
      else if(tmp[0] == '.'){
        abs_path = string(cur_dir) + tmp.substr(1,tmp.length());
      }
      else{
        abs_path = string(cur_dir)+"/"+tmp;
      }
      my_command.push_back(abs_path);
      tmp="";
    }
    else tmp+=command_string[i];
  }
  return;
}

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
}
