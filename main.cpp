/*============================================================
    @author - Rushitkumar Jasani   @rollno - 2018201034
=============================================================*/
#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif
/*============================================================
start of the programs.
sets the directory where the file runs as root.
lists the content of root and enters into non-canonical mode.
=============================================================*/
int main(int argc, char **argv){
  g_argc = argc;
  g_argv = argv;
  if(g_argc == 1) getcwd(root,sizeof(root));    //set root as current working dir.
  else if(g_argc == 2){
      strcpy(root,g_argv[1]);                   // setting root as default path.
  }
  else{
    cout << "too many arguments\n" << endl;
    exit(0);
  }
  strcat(cur_dir,root);
  back_stack.push(root);                         //back_stack saves history of visited dir.
  listdir(root);                                 //list directories inside root.
  enableNCanon();                                //enable non-canonical mode.
  return 0;
}
