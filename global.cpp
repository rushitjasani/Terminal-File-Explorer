/*============================================================
    @author - Rushitkumar Jasani   @rollno - 2018201034
=============================================================*/
#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

struct winsize terminal;
struct termios raw, newraw;
int g_argc = 0;
char ** g_argv;
char root[4096];
char cur_dir[4096];
std::vector <string> dlist;
std::stack <string> back_stack;
std::stack <string> forw_stack;
vector< string > my_command;
std::vector<char> command_string;
unsigned int cx=1;
unsigned int cy=1;
unsigned int term_row;
unsigned int term_col;
int cur_window = 0;
ofstream fout;
