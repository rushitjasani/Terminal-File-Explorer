#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

int main(int argc, char **argv){
  g_argc = argc;
  g_argv = argv;


  if(g_argc == 1) getcwd(root,sizeof(root));        //set root as current working dir.
  else if(g_argc == 2){
    for(int i=0; g_argv[1][i] != '\0';i++)root[i] = g_argv[1][i];
  }
  else{
    cout << "too many arguments" << endl;
    exit(0);
  }
  listdir(root);
  return 0;
}
