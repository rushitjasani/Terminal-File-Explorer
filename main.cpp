#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

int main(int argc, char **argv){
  g_argc = argc;
  g_argv = argv;
  if(g_argc == 1) getcwd(root,sizeof(root));                      //set root as current working dir.
  else if(g_argc == 2){
    strcpy(root,g_argv[1]);                               // setting root as default path.
  }
  else{
    cout << "too many arguments" << endl;
    exit(0);
  }
  /*cout << root << endl;
  sleep(5);*/
  strcat(cur_dir,root);
  b_space_track.push(root);
  listdir(root);                                                   //list directories inside root.
  enableNCanon();                                                  //enable non-canon mode.
  return 0;
}
