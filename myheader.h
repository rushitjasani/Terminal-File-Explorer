#include<bits/stdc++.h>
#include<stdio.h>
#include <dirent.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<termios.h>
#include <unistd.h>
using namespace std;

#ifndef MYHEADER_H
#define MYHEADER_H
#endif

extern int g_argc;            //global argc
extern char ** g_argv;        //global argv
extern char root[PATH_MAX];   //global root variable
int listdir(const char *);    //ls function
void display(const char *);   //to display like ls -a
