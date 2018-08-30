#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

bool goto_flag,search_flag_c;
int command_mode(){
  /*newraw.c_cc[VMIN] = 1;
  newraw.c_cc[VTIME] = 0;*/
  /*if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &newraw) != 0){
      fprintf(stderr,"Could not set attributes\n");
  }
  else{*/
    while(1){
      goto_flag = false;
      search_flag_c = false;
      cx = terminal.ws_row;
      cy = 1;
      CURSER;
      printf("\x1b[0K");
      printf(":");
      fflush(0);
      cy++;
      char ch;
      command_string.clear();
      my_command.clear();
      while(1){
        //read(STDIN_FILENO,ch,1);
        //if(ch[0] == 27 && ch[1]==0 && ch[2] == 0){
        ch = cin.get();
        if(ch == 27){
          cx = 1;
          cy = 1;
          CURSER;
          return 0;
        }

        else if(ch == 10){
          command_string.push_back(' ');
          split_command();
          function_call();
          if(goto_flag) return 1;
          if(search_flag_c) return 2;
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
  //}
  /*else if(ch[0] == 27 && ch[1] == '[' && (ch[2] == 'A' || ch[2]=='B')){
    continue;
  }
  else if(ch[0] == 27 && ch[1] == '[' && (ch[2] == 'C' || ch[2]=='D')){
    continue;
  }*/
  return 0;
}


void my_goto(){
  if(my_command.size() != 2) printf("Improper Arguments.");
  else{
    string goto_path = create_absolute_path(my_command[1]);
    back_stack.push(cur_dir);
    strcpy(cur_dir,goto_path.c_str());
    goto_flag = true;
  }
  return;
}
void search_recursive(string r_path, string name, vector<string> &search_result){
  DIR *dp;
  dp = opendir(r_path.c_str());
  struct dirent *d;
  if (dp == NULL){
    perror("opendir");
    return;
  }
  while((d = readdir(dp))){
    if(strcmp(d->d_name,".")==0 || strcmp(d->d_name,"..")==0) continue;
    else{
      string r_path_1 = r_path + "/" + string(d->d_name);
      //string p_path_1 = p_path + "/" + string(d->d_name);
      struct stat sb;
      stat(r_path_1.c_str(), &sb);
      if(strcmp(d->d_name,name.c_str()) == 0){
        search_result.push_back(r_path_1);
      }
      int isDir =  S_ISDIR(sb.st_mode);
      if(isDir){
          search_recursive(r_path_1,name,search_result);
      }
    }
  }
  return;
}
void my_search(){
  if(my_command.size() != 2) printf("Error");
  else{
    string name = my_command[1];
    std::vector<string> search_result;
    back_stack.push(cur_dir);
    search_recursive(cur_dir,name,search_result);
    if(search_result.size() == 0){
      cout << "No Match Found in " << cur_dir << endl;
      return;
    }
    write(STDOUT_FILENO, "\x1b[2J", 4); //to clear screen
    reset_curser_top();
    int vecsize = search_result.size();
    int root_len = strlen(root);
    for(int i=0; i < vecsize; i++){
        string t = search_result[i];
        t = t.substr(root_len, t.length()-root_len);
        search_result[i] = t;
        //t = create_absolute_path(t);
        display(t.c_str());
      }
      dlist.clear();
      dlist = search_result;
      search_flag_c = true;
      CURSER;
      //for(auto i:search_result)cout << i << endl;
  }
  return;
}

/*============================================================
take relative path and convert to absolute path for internal
system calls.
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
  cout << endl;
  for(;i<=command_string.size();i++){
    if(command_string[i] == ' ' && i>0  && command_string[i-1] != '\\' ){
      my_command.push_back(tmp);
      tmp = "";
    }
    else if(command_string[i] != '\\') tmp+=command_string[i];
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
    cx = terminal.ws_row;
    cy = 1;
    CURSER;
    printf("\x1b[0K");
    printf(":");
    cout << "command not found." << endl;
  }
  return;
}
