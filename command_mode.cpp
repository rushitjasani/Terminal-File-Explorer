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

bool goto_flag, search_flag_c;

/*============================================================
start point of command_mode.
Type command, erase with Backspace, go back to Normal Mode
by ESC, Up-Down-Left-Right are disabled.
returns 1 if user returns with Goto command.
returns 2 if user returns with search command.
=============================================================*/
int command_mode()
{
    while (1) {
        goto_flag = false;
        search_flag_c = false;
        cx = terminal.ws_row;
        cy = 1;
        CURSER;
        printf("\x1b[0K");
        printf(":");
        fflush(0);
        cy++;
        char ch[3] = { 0 };
        command_string.clear();
        my_command.clear();
        while (1) {
            if (read(STDIN_FILENO, ch, 3) == 0)
                continue;
            if (ch[0] == 27 && ch[1] == 0 && ch[2] == 0) {
                cx = 1;
                cy = 1;
                CURSER;
                return 0;
            }
            else if (ch[0] == 27 && ch[1] == '[' && (ch[2] == 'A' || ch[2] == 'B')) {
                continue;
            }
            else if (ch[0] == 27 && ch[1] == '[' && (ch[2] == 'C' || ch[2] == 'D')) {
                continue;
            }
            else if (ch[0] == 10) {
                command_string.push_back('\n');
                split_command();
                function_call();
                if (goto_flag)
                    return 1;
                if (search_flag_c)
                    return 2;
                break;
            }
            else if (ch[0] == 127) {
                if (cy > 2) {
                    cy--;
                    CURSER;
                    printf("\x1b[0K");
                    command_string.pop_back();
                }
            }
            else {
                cout << ch[0];
                cy++;
                CURSER;
                command_string.push_back(ch[0]);
            }
            fflush(0);
            memset(ch, 0, 3 * sizeof(ch[0]));
        }
    }
    return 0;
}

/*============================================================
lists the contents at given path and switch back to
normal mode.
=============================================================*/
void my_goto()
{
    if (my_command.size() != 2)
        printf("Improper Arguments.");
    else {
        string goto_path = create_absolute_path(my_command[1]);
        back_stack.push(cur_dir);
        strcpy(cur_dir, goto_path.c_str());
        goto_flag = true;
    }
    return;
}

/*============================================================
Helper function to my_search() for recursion.
=============================================================*/
void search_recursive(string r_path, string name, vector<string>& search_result)
{
    DIR* dp;
    dp = opendir(r_path.c_str());
    struct dirent* d;
    if (dp == NULL) {
        perror("opendir");
        return;
    }
    while ((d = readdir(dp))) {
        if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
            continue;
        else {
            string r_path_1 = r_path + "/" + string(d->d_name);
            if (strcmp(d->d_name, name.c_str()) == 0)
                search_result.push_back(r_path_1);
            if (isDirectory(r_path_1))
                search_recursive(r_path_1, name, search_result);
        }
    }
    return;
}

/*============================================================
search in current directory and gives search result.
mode changes to normal mode.
=============================================================*/
void my_search()
{
    if (my_command.size() != 2)
        printf("Error");
    else {
        string name = my_command[1];
        std::vector<string> search_result;
        back_stack.push(cur_dir);
        search_recursive(cur_dir, name, search_result);
        if (search_result.size() == 0) {
            cout << "No Match Found in " << cur_dir << endl;
            return;
        }
        write(STDOUT_FILENO, "\x1b[2J", 4);
        reset_curser_top();
        cy = 1;
        CURSER;
        int vecsize = search_result.size();
        int root_len = strlen(root);
        for (int i = 0; i < vecsize; i++) {
            string t = search_result[i];
            t = t.substr(root_len, t.length() - root_len);
            search_result[i] = t;
            display(t.c_str());
        }
        dlist.clear();
        dlist = search_result;
        search_flag_c = true;
        CURSER;
    }
    return;
}

/*============================================================
take command string, split it and put it in string vector.
use '\' as escape sequence to use space or other char in path.
=============================================================*/
void split_command()
{
    string tmp = "";
    unsigned int i = 0;
    cout << endl;
    for (; i < command_string.size(); i++) {
        if (command_string[i] == ' ' || command_string[i] == '\n' ) {
            if(tmp.size() > 0) my_command.push_back(tmp);
            tmp = "";
        }
        else if (command_string[i] == '\\')
            tmp += command_string[++i];
        else
            tmp += command_string[i];
    }
    return;
}

/*============================================================
calls various functions based on first argument of command.
=============================================================*/
void function_call()
{
    string s = my_command[0];
    if (s == "copy")
        my_copy();
    else if (s == "move")
        my_move();
    else if (s == "rename")
        my_rename();
    else if (s == "create_file")
        create_file();
    else if (s == "create_dir")
        create_dir();
    else if (s == "delete_file")
        delete_file();
    else if (s == "delete_dir")
        delete_dir();
    else if (s == "goto")
        my_goto();
    else if (s == "search")
        my_search();
    else if (s == "snapshot")
        snapshot();
    else {
        cx = terminal.ws_row;
        cy = 1;
        CURSER;
        printf("\x1b[0K");
        printf(":");
        cout << "command not found." << endl;
    }
    return;
}
