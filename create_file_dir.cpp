#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

void create_file(){
  if(my_command.size() < 3)printf("too few arguments.");
  else{
    string dest_folder =create_absolute_path(my_command[my_command.size()-1]);
    FILE *file_create;
    for(unsigned int i=1;i<my_command.size()-1;i++){
      string dest_path = dest_folder + "/" + my_command[i];
      file_create = fopen(dest_path.c_str(),"w");
      if(file_create == NULL) show_error();
      else show_success();
      fclose(file_create);
    }
  }
  return;
}
void create_dir(){
  if(my_command.size() < 3) printf("too few arguments");
  else{
    string dest_folder =create_absolute_path(my_command[my_command.size()-1]);
    for(unsigned int i=1;i<my_command.size()-1;i++){
      string dest_path = dest_folder + "/" + my_command[i];
      if(mkdir(dest_path.c_str(),0755) != 0)printf("Error");
    }
  }
  return;
}
