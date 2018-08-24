#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

extern int g_argc;              //global argc
extern char ** g_argv;          //global argv
extern char root[4096];         //global root variable
extern char cur_dir[4096];          //to maintain current dir
extern vector< string > dlist;      //global vector for dirctory names
extern stack <string> back_stack;
extern stack <string> forw_stack;
extern unsigned int cx;
extern unsigned int cy;
