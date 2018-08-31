/*============================================================
    @author - Rushitkumar Jasani   @rollno - 2018201034
=============================================================*/
#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

/*============================================================
helper function for DFS in snapshot recursively.
=============================================================*/
void snapshot_file(string d_path, string p_path){
  DIR *dp;
  dp = opendir(d_path.c_str());
  struct dirent *d;
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
        fout << name << endl;
        string tmp_path = d_path + "/" + name;
        if(isDirectory(tmp_path)) dir.push_back(name);
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
/*============================================================
snapshot <folder> <file>
=============================================================*/
void snapshot(){
  if(my_command.size() != 3)printf("improper arguments\n");
  else{
    string d_path = create_absolute_path(my_command[1]);
    if(!isDirectory(d_path)){
        cout << "First Argument must be valid Folder name." << endl;
        return;
    }
    string file_path = create_absolute_path(my_command[2]);
    if(isFileExist(file_path)){
        cout << "File Already Exist" << endl;
        return;
    }
    fout.open(file_path);
    snapshot_file(d_path,".");
    fout.close();
    cout << "snapshot saved" << endl;
  }
  return;
}
