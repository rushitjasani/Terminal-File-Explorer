#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

void snapshot_file(string d_path, string p_path){
  DIR *dp;
  dp = opendir(d_path.c_str());
  struct dirent *d;
  struct stat sb;
  vector<string> dir;
  if (dp == NULL){
    perror("opendir");
    return;
  }
  fout << p_path <<" :" << endl;
  while((d = readdir(dp))){
      if(strcmp(d->d_name,".")==0 || strcmp(d->d_name,"..")==0) continue;
      else{
        string name = string(d->d_name);
        if(name[0] == '.') continue;
        fout << name << endl;
        string tmp_path = d_path + "/" + name;
        stat(tmp_path.c_str(),&sb);
        int isDir = S_ISDIR(sb.st_mode);
        if(isDir) dir.push_back(name);
      }
  }
  fout << endl << endl;
  for(unsigned int i=0;i<dir.size();i++){
    string d1 = d_path + "/" + dir[i];
    string p1 = p_path + "/" + dir[i];
    snapshot_file(d1,p1);
  }
  return;

}
void snapshot(){
  if(my_command.size() != 3)printf("improper arguments");
  else{
    string d_path = create_absolute_path(my_command[1]);
    string file_path = create_absolute_path(my_command[2]);
    fout.open(file_path);
    snapshot_file(d_path,".");
    fout.close();
  }
}
