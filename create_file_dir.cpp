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
create file at path provided by user.
user can create multiple files at time also.
eg : create_file <f1> <f2> <f3> <Destination Folder>
=============================================================*/
void create_file()
{
    if (my_command.size() < 3)
        printf("too few arguments:\n");
    else {
        string dest_folder = create_absolute_path(my_command[my_command.size() - 1]);
        //verifies if destination is directory or not.
        if(!isDirectory(dest_folder)){
            cout << "Destination is not directory" << endl;
            return;
        }
        FILE* file_create;
        for (unsigned int i = 1; i < my_command.size() - 1; i++) {
            string dest_path = dest_folder + "/" + my_command[i];
            file_create = fopen(dest_path.c_str(), "w+");
            if (file_create == NULL)
                perror("");
            else
                cout << "file created" << endl;
            fclose(file_create);
        }
    }
    return;
}
/*============================================================
create directory at path provided by user.
user can create multiple directory at a time also.
eg : create_dir <d1> <d2> <d3> <Destination Folder>
=============================================================*/
void create_dir()
{
    if (my_command.size() < 3)
        printf("too few arguments\n");
    else {
        string dest_folder = create_absolute_path(my_command[my_command.size() - 1]);
        //verifies if destination is directory or not.
        if (!isDirectory(dest_folder)) {
            cout << "Destination is not directory." << endl;
            return;
        }
        for (unsigned int i = 1; i < my_command.size() - 1; i++) {
            string dest_path = dest_folder + "/" + my_command[i];
            if (mkdir(dest_path.c_str(), 0755) != 0)
                perror("");
            else
                cout << "directory created successfully." << endl;
        }
    }
    return;
}
