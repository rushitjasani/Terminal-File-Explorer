#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#define CURSER printf("%c[%d;%dH",27,cx,cy)

extern int g_argc;              //global argc
extern char ** g_argv;          //global argv
extern char root[4096];         //global root variable
extern char cur_dir[4096];          //to maintain current dir
extern vector< string > dlist;      //global vector for dirctory names
extern stack <string> back_stack;
extern stack <string> forw_stack;
extern vector <char> command_string;
extern unsigned int cx;
extern unsigned int cy;
extern unsigned int term_row;
extern int cur_window;
extern struct winsize terminal;
extern struct termios raw, newraw;
