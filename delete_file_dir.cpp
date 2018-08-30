#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

/*============================================================
deletes files that are given in list.
eg: delete_file <f1> <f2> <f3>
=============================================================*/
void delete_file(){
  if(my_command.size() < 2) printf("too few arguments\n");
  else{
    for(unsigned int i=1;i<my_command.size();i++){
      string remove_path = create_absolute_path(my_command[i]);
      if(remove(remove_path.c_str()) != 0)perror("");
      else cout << "Deleted :: " << my_command[i] << endl;
    }
  }
  return;
}
/*============================================================
Helper Function to delete recursively all files in
no empty directory.
=============================================================*/
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
      if(isDirectory(r_path)){
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
/*============================================================
deletes all directories at given list.
eg : delete_dir <d1> <d2> <d3>
=============================================================*/
void delete_dir(){
  if(my_command.size()<2)printf("too few arguments\n");
  else{
    for(unsigned int i=1;i<my_command.size();i++){
      string d_path = create_absolute_path(my_command[i]);
      if(!isDirectory(d_path)) {
          cout << "Not a Directory" << endl;
      }
      delete_recursive(d_path);
    }
  }
}
