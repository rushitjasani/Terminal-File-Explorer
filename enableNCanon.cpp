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

string parent = "..";
string current = ".";

bool search_flag = false;
/*============================================================
method to enter into Non-Canonical mode.
=============================================================*/
void enableNCanon()
{
    //getting the initial terminal settings
    tcgetattr(STDIN_FILENO, &raw);
    newraw = raw;
    //changing ICANON for entering Non Canonical mode.
    newraw.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
    newraw.c_iflag &= ~(BRKINT);
    //set new terminal settings.
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &newraw) != 0)
        fprintf(stderr, "Could not set attributes\n");
    else {
        char ch[3] = { 0 };
        while (1) {
            unsigned int tmp = terminal.ws_row;
            //cy = 1;
            printf("%c[%d;%dH", 27, tmp, 1);
            printf("::Normal Mode::");
            CURSER;
            fflush(0);
            if (read(STDIN_FILENO, ch, 3) == 0)
                continue;
            else if (ch[0] == 27 && ch[1] == '[' && ch[2] == 'A')
                UpArrow();
            else if (ch[0] == 27 && ch[1] == '[' && ch[2] == 'B')
                DownArrow();
            else if (ch[0] == 27 && ch[1] == '[' && ch[2] == 'C')
                RightArrow();
            else if (ch[0] == 27 && ch[1] == '[' && ch[2] == 'D')
                LeftArrow();
            else if (ch[0] == 'H' || ch[0] == 'h')
                HomeKey();
            else if (ch[0] == 127)
                BackspaceKey();
            else if (ch[0] == 10)
                EnterKey();
            else if (ch[0] == ':') {
                int ret = command_mode();
                cx = 1;
                CURSER;
                if (ret == 2) {
                    search_flag = true;
                    continue;
                }
                else
                    listdir(cur_dir);
            }
            else if (ch[0] == 'q') {
                write(STDOUT_FILENO, "\x1b[2J", 4);
                tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
                cx = 1;
                cy = 1;
                CURSER;
                exit(1);
            }
            fflush(0);
            memset(ch, 0, 3 * sizeof(ch[0]));
        }
    }
}
/*============================================================
method will handle behaviour when Up arrow key is pressed.
it also manages variables to map into vector and scroll.
=============================================================*/
void UpArrow()
{
    if (cx > 1) {
        cx--;
        CURSER;
    }
    else if (cx == 1 && cx + cur_window > 1) {
        cur_window--;
        //listdir(cur_dir);
        update_list();
        CURSER;
    }
}
/*============================================================
method will handle behaviour when Down arrow key is pressed.
it also manages variables to map into vector and scroll.
=============================================================*/
void DownArrow()
{

    if (cx <= term_row && cx < dlist.size()) {
        cx++;
        CURSER;
    }
    else if (cx > term_row && cx + cur_window < dlist.size()) {
        cur_window++;
        //listdir(cur_dir);
        update_list();
        CURSER;
    }
}
/*============================================================
RightArrow method will handle behaviour when Right arrow key is
pressed. if any path is there in forw_stack then pop it and
print content of that.
=============================================================*/
void RightArrow()
{
    reset_curser_top();
    if (!forw_stack.empty()) {
        string p = forw_stack.top();
        forw_stack.pop();
        strcpy(cur_dir, p.c_str());
        back_stack.push(cur_dir);
        listdir(cur_dir);
    }
}
/*============================================================
LeftArrow method will handle behaviour when Left arrow key is
pressed. if any path is there in back_stack then pop it and
print content of that.
=============================================================*/
void LeftArrow()
{
    reset_curser_top();
    if (back_stack.size() > 1) {
        string p = back_stack.top();
        forw_stack.push(p);
        back_stack.pop();
        p = back_stack.top();
        strcpy(cur_dir, p.c_str());
        listdir(cur_dir);
    }
    else if (back_stack.size() == 1) {
        string p = back_stack.top();
        strcpy(cur_dir, p.c_str());
        listdir(cur_dir);
    }
}
/*============================================================
Navigate to Home.
=============================================================*/
void HomeKey()
{
    reset_curser_top();
    strcpy(cur_dir, root);
    back_stack.push(cur_dir);
    while (!forw_stack.empty())
        forw_stack.pop();
    listdir(cur_dir);
}
/*============================================================
Navigate to Parent if exist. (root has no parent :P)
=============================================================*/
void BackspaceKey()
{
    if (search_flag)
        return;
    reset_curser_top();
    if ((strcmp(cur_dir, root)) != 0) {
        string s_name = SplitFilename(string(cur_dir));
        strcpy(cur_dir, s_name.c_str());
        back_stack.push(cur_dir);
        while (!forw_stack.empty())
            forw_stack.pop();
        listdir(cur_dir);
    }
    else {
    }
}
/*============================================================
if EnterKey pressed on directory then go to dir. else opens
file in default application.
=============================================================*/
void EnterKey()
{
    if (dlist[cur_window + cx - 1] == current) {
        // if selected directory is '.' .
        reset_curser_top();
        listdir(cur_dir);
    }
    else if (dlist[cur_window + cx - 1] == parent) {
        // if selected directory is '..' .
        string s_name = cur_dir;
        s_name = SplitFilename(s_name);
        strcpy(cur_dir, s_name.c_str());
        back_stack.push(cur_dir);
        while (!forw_stack.empty())
            forw_stack.pop();
        reset_curser_top();
        listdir(cur_dir);
    }
    else {
        // if selected directory is except '.' and '..'.
        // taking file name and making full path
        char* p_path;
        char* f_path;
        if (!search_flag) {
            string cur_d = "/" + dlist[cur_window + cx - 1];
            CURSER;
            p_path = cur_dir;
            f_path = new char[cur_d.length() + strlen(p_path) + 1];
            strcpy(f_path, p_path);
            strcat(f_path, cur_d.c_str());
            strcpy(cur_dir, f_path);
        }
        else {
            string search_path = create_absolute_path(dlist[cur_window + cx - 1]);
            strcpy(cur_dir, search_path.c_str());
            f_path = new char[strlen(cur_dir) + 5];
            strcpy(f_path, cur_dir);
        }
        //Maintaing forward and backward stacks.
        back_stack.push(cur_dir);
        //clear forward stack if entering in any directory manually.
        while (!forw_stack.empty())
            forw_stack.pop();
        //check if selected file is FILE or DIRECTORY.
        if (isDirectory(f_path)) {
            reset_curser_top();
            listdir(cur_dir);
            search_flag = false;
        }
        else {
            back_stack.pop();
            string top = back_stack.top();
            strcpy(cur_dir, top.c_str());
            int bridge[2];
            if(pipe(bridge) == -1) perror("");
            pid_t pid = fork();
            if (pid == 0) {
                // close(2);
                // execlp("xdg-open", "xdg-open", f_path, NULL);
                // exit(0);
                dup2(bridge[1],STDOUT_FILENO);
                close(bridge[1]);
                close(bridge[0]);
                execlp("xdg-mime", "xdg-mime", "query", "filetype",f_path, NULL);
            }
            char ftype[50];
            int x = read(bridge[0],ftype,50);
            ftype[x-1] = '\0';
            close(bridge[0]);
            fflush(stdout);
            fflush(stdin);
            
            int bridge1[2];
            if(pipe(bridge1) == -1) perror("");
            pid = fork();
            if (pid == 0) {
                dup2(bridge1[1],STDOUT_FILENO);
                close(bridge1[0]);
                //write(STDOUT_FILENO,".",strlen("."));
                if(execlp("xdg-mime", "xdg-mime", "query", "default",ftype, NULL) == -1){
                    exit(0);
                }
                close(bridge1[1]);
            }
            //int present_chars = 0;
            char fapp[50];
            read(bridge1[0],fapp,50);
            fapp[x+1] = '\0';
            close(bridge1[0]);
            fflush(stdout);
            fflush(stdin);
            cout << "~~~" << fapp << "~~~" << "OK";
        }
    }
}
