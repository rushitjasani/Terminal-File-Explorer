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
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal);
  term_row = terminal.ws_row - 2 ;
  write(STDOUT_FILENO, "\x1b[2J", 4); //to clear screen
  CURSER;
  struct dirent *d;
  DIR *dp;
  dp = opendir(path);
  if (dp == NULL){
    perror("opendir");
    return -1;
  }

  dlist.clear();

  while((d = readdir(dp))){
    if(strcmp(path, root) == 0){
      strcpy(cur_dir,root);
      if(strcmp(d->d_name,"..") == 0) continue;
      }
      dlist.push_back(d->d_name);
  }
  sort(dlist.begin(),dlist.end());
  int vecsize = dlist.size();

  int from = cur_window;
  int to;
  if((unsigned)vecsize <= term_row) to = vecsize-1;
  else to = term_row+cur_window;

  for(int i=from; i <= to; i++){
      string t = dlist[i];
      display(t.c_str());
    }
  CURSER;
  closedir(dp);
  return 0;
}

void display(const char *dirName){
  struct stat sb;
  stat(dirName, &sb);
  string t_ime = string(ctime(&sb.st_mtime));
  t_ime[t_ime.length()-1] = '\0';
  printf( (S_ISDIR(sb.st_mode) ) ? "d" : "-" );
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
  printf("\t%s",t_ime.c_str());
  printf("\t%-20s\n",dirName);
}
