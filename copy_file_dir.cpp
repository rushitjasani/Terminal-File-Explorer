#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

void file_copy(string from, string to){
  FILE *from_f,*to_f;
  char c;
  if((from_f = fopen(from.c_str(),"r")) == NULL ){
    perror("");
    return;
  }
  if((to_f = fopen(to.c_str(),"w")) == NULL){
    perror("");
    return;
  }
  while(!feof(from_f)){
    c = getc(from_f);
    putc(c,to_f);
  }
  struct stat from_stat;
  stat(from.c_str(),&from_stat);
  chown(to.c_str(),from_stat.st_uid,from_stat.st_gid);
  chmod(to.c_str(),from_stat.st_mode);
  fclose(from_f);
  fclose(to_f);
}
void directory_copy(string from, string to){
  DIR *dp;
  dp = opendir(from.c_str());
  struct dirent *d;
  if (dp == NULL){
    perror("opendir");
    return;
  }
  while((d = readdir(dp))){
    if(strcmp(d->d_name,".")==0 || strcmp(d->d_name,"..")==0) continue;
    else{
      string from_path = from + "/" + string(d->d_name);
      string to_path = to + "/" + string(d->d_name);
      struct stat sb;
      stat(from_path.c_str(), &sb);
      int isDir =  S_ISDIR(sb.st_mode);
      if(isDir){
          mkdir(to_path.c_str(),0755);
          directory_copy(from_path,to_path);
      }
      else{
          file_copy(from_path.c_str(),to_path.c_str());
      }
    }
  }
  closedir(dp);
  return;
}
void my_copy(){
  if(my_command.size() < 3)printf("improper arguments");
  else{
    string dest_folder = create_absolute_path(my_command[my_command.size()-1]);
    for(unsigned int i=1;i<my_command.size()-1;i++){
      string from_path = create_absolute_path(my_command[i]);
      size_t found=from_path.find_last_of("/\\");
      string to_path = dest_folder + "/" + from_path.substr(found+1,from_path.length()-found);
      struct stat sb;
      stat(from_path.c_str(), &sb);
      int isDir =  S_ISDIR(sb.st_mode);
      if(isDir){
        if(mkdir(to_path.c_str(),0755) != 0){
            perror("");
            return;
        }
        //check and set permission as prev folder.
        directory_copy(from_path,to_path);
      }
      else{
          file_copy(from_path,to_path);
      }
    }
  }
  return;
}
