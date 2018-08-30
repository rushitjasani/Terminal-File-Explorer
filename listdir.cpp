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
  update_list();
  closedir(dp);
  return 0;
}
void update_list(){
  write(STDOUT_FILENO, "\x1b[2J", 4); //to clear screen
  cy = 1;
  CURSER;
  int vecsize = dlist.size();
  int from = cur_window;
  int to;
  if((unsigned)vecsize <= term_row) to = vecsize-1;
  else to = term_row+cur_window;
  //cout << from << "##" << to << "##" << vecsize;
  //sleep(5);
  for(int i=from; i <= to; i++){
      string t = dlist[i];
      display(t.c_str());
    }
  CURSER;
  return;
}
void display(const char *dirName){
  struct stat sb;
  string abs_path = create_absolute_path(dirName);
  stat(abs_path.c_str(), &sb);
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  printf("b");                break;
    case S_IFCHR:  printf("c");                break;
    case S_IFDIR:  printf("d");                break;
    case S_IFIFO:  printf("p");                break;
    case S_IFLNK:  printf("l");                break;
    case S_IFREG:  printf("-");                break;
    case S_IFSOCK: printf("s");                break;
    default:       printf("-");                break;
    }
  printf( (sb.st_mode & S_IRUSR ) ? "r" : "-" );
  printf( (sb.st_mode & S_IWUSR ) ? "w" : "-" );
  printf( (sb.st_mode & S_IXUSR ) ? "x" : "-" );
  printf( (sb.st_mode & S_IRGRP ) ? "r" : "-" );
  printf( (sb.st_mode & S_IWGRP ) ? "w" : "-" );
  printf( (sb.st_mode & S_IXGRP ) ? "x" : "-" );
  printf( (sb.st_mode & S_IROTH ) ? "r" : "-" );
  printf( (sb.st_mode & S_IWOTH ) ? "w" : "-" );
  printf( (sb.st_mode & S_IXOTH ) ? "x" : "-" );
  printf("%8lu",sb.st_nlink);

  struct passwd *get_username;
  get_username = getpwuid(sb.st_uid);
  string uname = get_username->pw_name;
  printf("\t%s",uname.c_str());

  struct group *get_grpname;
  get_grpname = getgrgid(sb.st_gid);
  string gname = get_grpname->gr_name;
  printf("\t%s",gname.c_str());

  long long x = sb.st_size;
  if(x > 1024) printf("\t%8lld K",x/1024);
  else printf("\t%8lld B",x);
  string m_time = string(ctime(&sb.st_mtime));
  m_time = m_time.substr(4,20);
  printf("\t  %s",m_time.c_str());
  printf("  %-20s\n",dirName);
}
