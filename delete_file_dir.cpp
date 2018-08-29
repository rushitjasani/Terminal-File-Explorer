#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif


void delete_file(){
  if(my_command.size() < 2) printf("too few arguments");
  else{
    for(unsigned int i=1;i<my_command.size();i++){
      string remove_path = create_absolute_path(my_command[i]);
      if(remove(remove_path.c_str()) != 0)show_error();
      else show_success();
    }
  }
  return;
}
void delete_recursive(string d_path){
  DIR *dp;
  dp = opendir(d_path.c_str());
  struct dirent *d;
  if (dp == NULL){
    perror("opendir");
    return;
  }
  while((d = readdir(dp))){
    if(strcmp(d->d_name,".")==0 || strcmp(d->d_name,"..")==0) continue;
    else{
      string r_path = d_path + "/" + string(d->d_name);
      struct stat sb;
      stat(r_path.c_str(), &sb);
      int isDir =  S_ISDIR(sb.st_mode);
      if(isDir){
          delete_recursive(r_path);
      }
      else{
          remove(r_path.c_str());
      }
    }
  }
  rmdir(d_path.c_str());
  closedir(dp);
  return;
}
void delete_dir(){
  if(my_command.size()<2)printf("too few args");
  else{
    for(unsigned int i=1;i<my_command.size();i++){
      string d_path = create_absolute_path(my_command[i]);
      delete_recursive(d_path);
    }
  }
}
