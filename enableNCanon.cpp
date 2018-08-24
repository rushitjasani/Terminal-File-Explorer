#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

struct termios raw, newraw;

void enableNCanon(){
  //getting the initial terminal settings
  tcgetattr(STDIN_FILENO, &raw);
  atexit(disableNCanon);
  newraw = raw;

  //changing ICANON for entering Non Canonical mode.
  newraw.c_lflag &= ~ICANON;
  newraw.c_lflag &= ~ECHO;
  //newraw.c_cc[VMIN] = 0;
  //newraw.c_cc[VTIME] = 1;

  //set new terminal settings.
  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &newraw) != 0) {
    fprintf(stderr,"Could not set attributes\n");
  }
  else{
    write(STDOUT_FILENO, "\x1b[H", 3);
    string parent = "..";
    string current = ".";
    cx = 0;
    cy = 0;
    char ch;
    while(1){
      ch=cin.get();
      //chech for first char and if ESC then go inside loop.
      if(ch==27)
      {
        ch=cin.get(); // scans [ .
        ch=cin.get(); // scans third char of escape sequence.
        if(ch=='A'){
          //DOWN ARROW
          write(STDOUT_FILENO, "\x1b[1A", 4);
          if(cx > 0)cx--;
        }
        else if(ch=='B'){
          //UP ARROW
          if(dlist.size()-1 >  cx )
            {
              write(STDOUT_FILENO, "\x1b[1B", 4);
              cx++;
            }
        }
        else if(ch=='C'){
          //RIGHT ARROW (FORWARD)
          if(!forw_stack.empty()){
              string p = forw_stack.top();
              forw_stack.pop();
              strcpy(cur_dir, p.c_str());
              back_stack.push(cur_dir);
              listdir(cur_dir);
          }
          else continue;
        }
        else if(ch=='D'){
          //LEFT ARROW (BACKWORD)
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
        else{
            continue;
        }
      }
      else if(ch=='H' || ch=='h'){
              //'H' or 'h' HANDLE
              strcpy(cur_dir,root);
              back_stack.push(cur_dir);
              while(!forw_stack.empty()) forw_stack.pop();
              listdir(cur_dir);
      }
      else if(ch==127){
        //BACKSPACE HANDLE
        if((strcmp(cur_dir,root)) != 0 ){
          string s_name = SplitFilename(string(cur_dir));
          strcpy(cur_dir,s_name.c_str());
          back_stack.push(cur_dir);
          while(!forw_stack.empty()) forw_stack.pop();
          listdir(cur_dir);
        }

      }
      else if(ch == 10){
        // ENTER KEY HANDLE
        if(dlist[cx] == current){
          // if selected directory is '.' .
              listdir(cur_dir);
        }
        else if(dlist[cx] == parent ){
          // if selected directory is '..' .
          string s_name = cur_dir;
          s_name = SplitFilename(s_name);
          strcpy(cur_dir,s_name.c_str());
          back_stack.push(cur_dir);
          while(!forw_stack.empty()) forw_stack.pop();
          listdir(cur_dir);
        }
        else{
          // if selected directory is except '.' and '..'.
          // taking file name and making full path
          string cur_d = "/" + dlist[cx];
          if(dlist.size()-1 >  cx ) cx++;
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
            listdir(f_path);
          }
          else if( S_ISREG(sb.st_mode) ){
            //if FILE then open by xdg-open.
            string op = "xdg-open " + string(f_path);
            if(system(op.c_str()) == -1) continue;
          }
        }
      }
    }
  }
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);
  exit(0);
}
