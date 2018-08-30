#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

/*============================================================
move function :
move <source> <destination folder>
=============================================================*/
void my_move(){
  if(my_copy() == 1) return;
  my_command.pop_back();
  if(my_command.size()<2)printf("too few arguments\n");
  else{
    for(unsigned int i=1;i<my_command.size();i++){
      string d_path = create_absolute_path(my_command[i]);
      if(isDirectory(d_path)) delete_recursive(d_path);
      else  {
        if(remove(d_path.c_str()) == -1) perror("");
      }
    }
  }
  return;
}
/*============================================================
rename function :
rename <old> <new>
=============================================================*/
void my_rename(){
  if(my_command.size()!=3)printf("Improper Arguments\n");
  else{
      string old = create_absolute_path(my_command[1]);
      string new_ = create_absolute_path(my_command[2]);
      if(rename(old.c_str(),new_.c_str()) == -1) perror("");
      else cout << "Done" << endl;
  }
  return;
}
