/*============================================================
    @author - Rushitkumar Jasani   @rollno - 2018201034
=============================================================*/
#ifndef MYHEADER_H
#define MYHEADER_H
#include "myheader.h"
#endif

#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

/*============================================================
takes path and returns parent as a path by removing
file or folder name at end.
=============================================================*/
string SplitFilename(string str)
{
    size_t found;
    found = str.find_last_of("/\\");
    return str.substr(0, found);
}

/*============================================================
take relative path and convert to absolute path for internal
system calls.
=============================================================*/
string create_absolute_path(string r_path)
{
    string abs_path = "";
    if (r_path[0] == '~') {
        r_path = r_path.substr(1, r_path.length());
        abs_path = string(root) + r_path;
    }
    else if (r_path[0] == '/') {
        abs_path = string(root) + r_path;
    }
    else if (r_path[0] == '.' && r_path[1] == '/') {
        abs_path = string(cur_dir) + r_path.substr(1, r_path.length());
    }
    else {
        abs_path = string(cur_dir) + "/" + r_path;
    }
    return abs_path;
}

/*============================================================
reset the curser position at top (1,1) position.
=============================================================*/
void reset_curser_top()
{
    cx = 1;
    //cy = 1;
    cur_window = 0;
    CURSER;
}

/*============================================================
takes path and check if directory or not.
=============================================================*/
bool isDirectory(string path)
{
    struct stat sb;
    if (stat(path.c_str(), &sb) != 0) {
        perror(path.c_str());
        return false;
    }
    if (S_ISDIR(sb.st_mode))
        return true;
    else
        return false;
}
/*============================================================
checks if file already exist or not.
=============================================================*/
int isFileExist(string path)
{
    FILE* file;
    if ((file = fopen(path.c_str(), "r"))) {
        fclose(file);
        return 1;
    }
    return 0;
}
