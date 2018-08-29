#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

void my_move(){
  my_copy();
  my_command.pop_back();

  if(my_command.size()<2)printf("too few arguments\n");
  else{
    for(unsigned int i=1;i<my_command.size();i++){
      string d_path = create_absolute_path(my_command[i]);
      struct stat sb;
      stat(d_path.c_str(), &sb);
      int isDir =  S_ISDIR(sb.st_mode);
      if(isDir) delete_recursive(d_path);
      else  remove(d_path.c_str());
    }
  }
  return;
}
