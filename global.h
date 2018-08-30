#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#define CURSER printf("%c[%d;%dH",27,cx,cy)

extern int g_argc;                      //global argc.
extern char ** g_argv;                  //global argv.
extern char root[4096];                 //global root variable.
extern char cur_dir[4096];              //to maintain current dir.
extern vector< string > dlist;          //global vector for dirctory names.
extern stack <string> back_stack;       //to store prev visited dir.
extern stack <string> forw_stack;       //opposite of back_stack.
extern vector <char> command_string;    //to store char by char info in command mode.
extern unsigned int cx;                 //curser position x.
extern unsigned int cy;                 //curser position y.
extern unsigned int term_row;           //num of row in terminal.
extern int cur_window;                  //helper var in scrolling.
extern struct winsize terminal;         //to get terminal window config.
extern struct termios raw, newraw;      //to get terminal configuration.
extern vector< string > my_command;     //store command tockens in command mode.
extern ofstream fout;                   //for storing snapshot, to open file.
