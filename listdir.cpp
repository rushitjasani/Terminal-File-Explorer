#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

//list directory in currnet dir.
int listdir(const char *path)
{
  struct dirent *d;
  DIR *dp;
  dp = opendir(path);
  if (dp == NULL){
    perror("opendir");
    return -1;
  }
  while((d = readdir(dp))) display(d->d_name);
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
