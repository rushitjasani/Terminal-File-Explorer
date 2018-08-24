#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif
#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

//list directory in currnet dir.
int listdir(const char *path)
{
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);
  struct dirent *d;
  DIR *dp;
  dp = opendir(path);
  if (dp == NULL){
    perror("opendir");
    return -1;
  }
  dlist.clear();
  cx = 0;
  cy = 0;
  while((d = readdir(dp))){
    /*if(b_space_track.size() == 1){
      strcpy(cur_dir,root);
      if(strcmp(d->d_name,"..") == 0) continue;
    }*/
    if(strcmp(path, root) == 0){
      strcpy(cur_dir,root);
      if(strcmp(d->d_name,"..") == 0) continue;
    }
    dlist.push_back(d->d_name);
    display(d->d_name);
  }
  write(STDOUT_FILENO, "\x1b[H", 3);
  closedir(dp);
  return 0;
}

void display(const char *dirName){
  struct stat sb;
  stat(dirName, &sb);
  printf("%-20s",dirName);
  cout << "\t";
  printf( (sb.st_mode & S_IRUSR ) ? "r" : "-" );
  printf( (sb.st_mode & S_IWUSR ) ? "w" : "-" );
  printf( (sb.st_mode & S_IXUSR ) ? "x" : "-" );
  printf( (sb.st_mode & S_IRGRP ) ? "r" : "-" );
  printf( (sb.st_mode & S_IWGRP ) ? "w" : "-" );
  printf( (sb.st_mode & S_IXGRP ) ? "x" : "-" );
  printf( (sb.st_mode & S_IROTH ) ? "r" : "-" );
  printf( (sb.st_mode & S_IWOTH ) ? "w" : "-" );
  printf( (sb.st_mode & S_IXOTH ) ? "x" : "-" );
  printf("\t%10lld bytes",(long long) sb.st_size );
  printf("\t%s",ctime(&sb.st_mtime));
}
