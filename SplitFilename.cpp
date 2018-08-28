#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

string SplitFilename(string str)
{
  size_t found;
  found=str.find_last_of("/\\");
  return str.substr(0,found); 
}
