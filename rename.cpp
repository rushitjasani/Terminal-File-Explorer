#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

void my_rename(){
  if(my_command.size()!=3)printf("Improper Arguments\n");
  else{
      string old = create_absolute_path(my_command[1]);
      string new_ = create_absolute_path(my_command[2]);
      if(rename(old.c_str(),new_.c_str()) != 0) perror("");
      else cout << "Done" << endl;
  }
  return;
}
