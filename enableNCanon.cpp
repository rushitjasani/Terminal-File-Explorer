#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

string parent = "..";
string current = ".";

void enableNCanon(){
  //getting the initial terminal settings
  tcgetattr(STDIN_FILENO, &raw);
  newraw = raw;

  //changing ICANON for entering Non Canonical mode.
  newraw.c_lflag &= ~ICANON;
  newraw.c_lflag &= ~ECHO;

  //set new terminal settings.
  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &newraw) != 0)
    fprintf(stderr,"Could not set attributes\n");
  else{
    char ch;
    while(1){
      unsigned int tmp = terminal.ws_row;
      printf("%c[%d;%dH",27,tmp,cy);
      printf(":::::Normal Mode:::::");
      CURSER;
      ch=cin.get();
      //check for first char and if ESC then go inside loop.
      if(ch==27){
        ch=cin.get(); // scans [ .
        ch=cin.get(); // scans third char of escape sequence.
        if(ch=='A')               UpArrow();
        else if(ch=='B')          DownArrow();
        else if(ch=='C')          RightArrow();
        else if(ch=='D')          LeftArrow();
        else                      continue;
      }
      else if(ch=='H' || ch=='h') HomeKey();
      else if(ch==127)            BackspaceKey();
      else if(ch == 10)           EnterKey();
      else if(ch == ':')          command_mode();
      else if(ch == 'q'){
        write(STDOUT_FILENO, "\x1b[2J", 4);
        exit(0);
      }
    }
  }
}

void UpArrow(){
  if(cx > 1)
  {
    cx--;
    CURSER;
  }
  else if(cx == 1 && cx+cur_window > 1 ){
    cur_window--;
    listdir(cur_dir);
    CURSER;
  }
}

void DownArrow(){
  //cout << cx << "##" << cur_window << "##" << dlist.size();
  if(cx <= term_row && cx < dlist.size())
  {
    cx++;
    CURSER;
  }
  else if(cx > term_row && cx+cur_window < dlist.size() ){
    cur_window++;
    listdir(cur_dir);
    CURSER;
  }
}

void RightArrow(){
  cx = 1;
  CURSER;
  if(!forw_stack.empty()){
      string p = forw_stack.top();
      forw_stack.pop();
      strcpy(cur_dir, p.c_str());
      back_stack.push(cur_dir);
      listdir(cur_dir);
  }
}

void LeftArrow(){
  cx = 1;
  CURSER;
  if(back_stack.size() > 1){
      string p = back_stack.top();
      forw_stack.push(p);
      back_stack.pop();
      p = back_stack.top();
      strcpy(cur_dir, p.c_str());
      listdir(cur_dir);
  }
  else if(back_stack.size() == 1){
    string p = back_stack.top();
    strcpy(cur_dir, p.c_str());
    listdir(cur_dir);
  }
}

void HomeKey(){
  cx = 1;
  CURSER;
  strcpy(cur_dir,root);
  back_stack.push(cur_dir);
  while(!forw_stack.empty()) forw_stack.pop();
  listdir(cur_dir);
}

void BackspaceKey(){
  cx = 1;
  CURSER;
  if((strcmp(cur_dir,root)) != 0 ){
    string s_name = SplitFilename(string(cur_dir));
    strcpy(cur_dir,s_name.c_str());
    back_stack.push(cur_dir);
    while(!forw_stack.empty()) forw_stack.pop();
    listdir(cur_dir);
  }
}

void EnterKey(){
  if(dlist[cur_window+cx-1] == current){
    // if selected directory is '.' .
        cx = 1;
        cur_window = 0;
        listdir(cur_dir);
  }
  else if(dlist[cur_window+cx-1] == parent ){
    // if selected directory is '..' .
    string s_name = cur_dir;
    s_name = SplitFilename(s_name);
    strcpy(cur_dir,s_name.c_str());
    back_stack.push(cur_dir);
    while(!forw_stack.empty()) forw_stack.pop();
    cx = 1;
    cur_window = 0;
    listdir(cur_dir);
  }
  else{
    // if selected directory is except '.' and '..'.
    // taking file name and making full path
    string cur_d = "/" + dlist[cur_window+cx-1];
    CURSER;
    char *p_path = cur_dir;
    char *f_path = new char[cur_d.length() + strlen(p_path) + 1];
    strcpy(f_path,p_path);
    strcat(f_path, cur_d.c_str());
    strcpy(cur_dir,f_path);
    //Maintaing forward and backward stacks.
    back_stack.push(f_path);
    //clear forward stack if entering in any directory manually.
    while(!forw_stack.empty()) forw_stack.pop();
    //check if selected file is FILE or DIRECTORY.
    struct stat sb;
    stat(f_path, &sb);
    if( S_ISDIR(sb.st_mode) ){
      cx = 1;
      cur_window = 0;
      listdir(f_path);
    }
    else if( S_ISREG(sb.st_mode) ){
      //if FILE then open by xdg-open.
      back_stack.pop();
      string top = back_stack.top();
      strcpy(cur_dir,top.c_str());
      string op = "bash -c 'xdg-open " + string(f_path) + "' 2> /dev/null ";
      system(op.c_str());
      CURSER;
    }
  }
}
