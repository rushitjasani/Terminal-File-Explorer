#include<bits/stdc++.h>
#include<stdio.h>
#include <dirent.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<termios.h>
#include <unistd.h>
#include<sys/ioctl.h>
#include <fcntl.h>
#include <pwd.h>
#include<grp.h>        //for username and groupname from userid and grpid.
using namespace std;

#ifndef MYHEADER_H
#define MYHEADER_H
#endif


int listdir(const char *);    //ls function.
void display(const char *);   //to display like ls -a.
void enableNCanon();          //to enter into Normal mode.
string SplitFilename(string );  //returns path to given file or folder.
void UpArrow();
void DownArrow();
void LeftArrow();
void RightArrow();
void HomeKey();
void EnterKey();
void BackspaceKey();
int command_mode();
void split_command();
void function_call();
void my_copy();
void file_copy(string, string);
void directory_copy(string, string);
void my_move();
void my_rename();
void create_file();
void create_dir();
void delete_file();
void delete_recursive(string);
void delete_dir();
void my_goto();
void my_search();
void snapshot_file(string, string);
void snapshot();
string create_absolute_path(string);
void reset_curser_top();
void update_list();
