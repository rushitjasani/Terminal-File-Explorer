
#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

int g_argc = 0;
char ** g_argv;
char root[4096];
char cur_dir[4096];
std::vector <string> dlist;
std::stack <string> back_stack;
std::stack <string> forw_stack;
unsigned int cx=1;
unsigned int cy=0;
unsigned int term_row;
int cur_window = 0;
