#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

struct termios raw, newraw;

void disableNCanon(){
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);
}


string SplitFilename(string str)
{
  size_t found;
  found=str.find_last_of("/\\");
  return str.substr(0,found);
}

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
      if(ch==27)
      {
        ch=cin.get();
        ch=cin.get();
        if(ch=='A'){
          write(STDOUT_FILENO, "\x1b[1A", 4);
          if(cx > 0)cx--;
        }
        else if(ch=='B'){
          if(dlist.size()-1 >  cx )
            {
              write(STDOUT_FILENO, "\x1b[1B", 4);
              cx++;
            }
        }
        else if(ch=='C'){

        }
        else if(ch=='D'){

        }
        else{
            continue;
        }
      }
      else if(ch=='H' || ch=='h'){
              while(b_space_track.size() != 1)b_space_track.pop();
              strcpy(cur_dir,root);
              listdir(cur_dir);
      }
      else if(ch==127){
        if(b_space_track.size() > 1) b_space_track.pop();
        string cur_dir = b_space_track.top();
        listdir(cur_dir.c_str());
      }
      else if(ch == 10){
        //cout << dlist[cx] << endl;
        if(dlist[cx] == current){
              listdir(cur_dir);
        }
        else if(dlist[cx] == parent ){
          b_space_track.pop();
          string s_name = cur_dir;
          s_name = SplitFilename(s_name);
          strcpy(cur_dir,s_name.c_str());
          listdir(cur_dir);
        }
        else{
          string cur_d = "/" + dlist[cx];
          if(dlist.size()-1 >  cx ) cx++;
          char *p_path = cur_dir;
          char *f_path = new char[cur_d.length() + strlen(p_path) + 1];
          strcpy(f_path,p_path);
          strcat(f_path, cur_d.c_str());
          b_space_track.push(f_path);
          strcpy(cur_dir,f_path);
          struct stat sb;
          stat(f_path, &sb);
          if( S_ISDIR(sb.st_mode) ){
            int i;
            for(i=0;f_path[i]!= '\0' ;i++)cur_dir[i] =f_path[i];
            f_path[i] = '\0';
            listdir(f_path);
          }
          else if( S_ISREG(sb.st_mode) ){
            string op = "xdg-open " + string(f_path);
            if(system(op.c_str()) == -1) continue;
          }
        }

      }
      else
      {

      }
    }
  }
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);
  exit(0);
}
