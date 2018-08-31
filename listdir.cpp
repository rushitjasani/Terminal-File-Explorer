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
takes directory path, opens it and store all it's content
into dlist vector for display.
=============================================================*/
int listdir(const char* path)
{
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal);
    term_row = terminal.ws_row - 2;
    term_col = terminal.ws_col;
    write(STDOUT_FILENO, "\x1b[2J", 4); //to clear screen
    struct dirent* d;
    DIR* dp;
    dp = opendir(path);
    if (dp == NULL) {
        perror("opendir");
        return -1;
    }
    dlist.clear();
    while ((d = readdir(dp))) {
        if (strcmp(path, root) == 0) {
            strcpy(cur_dir, root);
            if (strcmp(d->d_name, "..") == 0)
                continue;
        }
        dlist.push_back(d->d_name);
    }
    sort(dlist.begin(), dlist.end());
    update_list();
    cx = 1;
    //cy = 1;
    CURSER;
    //reset_curser_top();
    closedir(dp);
    return 0;
}
/*============================================================
takes each name from dlist and calls display() for output.
this method also helps in scrolling as it prints contents
mapped by cursor position and relative to terminal size.
=============================================================*/
void update_list()
{
    write(STDOUT_FILENO, "\x1b[2J", 4); //to clear screen
    cy = 1;
    CURSER;
    int vecsize = dlist.size();
    int from = cur_window;
    int to;
    if ((unsigned)vecsize <= term_row)
        to = vecsize - 1;
    else
        to = term_row + cur_window;
    for (int i = from; i <= to; i++) {
        string t = dlist[i];
        display(t.c_str());
    }
    return;
}
/*============================================================
shows long listing for given path.
=============================================================*/
void display(const char* dirName)
{
    cy = 0;
    struct stat sb;
    string abs_path = create_absolute_path(dirName);
    stat(abs_path.c_str(), &sb);
    switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
        printf("b");
        break; //block file
    case S_IFCHR:
        printf("c");
        break; //device file
    case S_IFDIR:
        printf("d");
        break; //directory
    case S_IFIFO:
        printf("p");
        break; //FIFO file
    case S_IFLNK:
        printf("l");
        break; //link
    case S_IFREG:
        printf("-");
        break; //normal file
    case S_IFSOCK:
        printf("s");
        break; //socket file
    default:
        printf("-");
        break;
    }
    printf((sb.st_mode & S_IRUSR) ? "r" : "-");
    printf((sb.st_mode & S_IWUSR) ? "w" : "-");
    printf((sb.st_mode & S_IXUSR) ? "x" : "-");
    printf((sb.st_mode & S_IRGRP) ? "r" : "-");
    printf((sb.st_mode & S_IWGRP) ? "w" : "-");
    printf((sb.st_mode & S_IXGRP) ? "x" : "-");
    printf((sb.st_mode & S_IROTH) ? "r" : "-");
    printf((sb.st_mode & S_IWOTH) ? "w" : "-");
    printf((sb.st_mode & S_IXOTH) ? "x" : "-");
    cy += 10;

    struct passwd* get_username;
    get_username = getpwuid(sb.st_uid);
    string uname = get_username->pw_name;
    cy += printf(" %10s ", uname.c_str());

    struct group* get_grpname;
    get_grpname = getgrgid(sb.st_gid);
    string gname = get_grpname->gr_name;
    cy += printf(" %10s ", gname.c_str());

    long long x = sb.st_size;
    if (x >= (1 << 30))
        cy += printf("%4lldG ", x / (1 << 30));
    else if (x >= (1 << 20))
        cy += printf("%4lldM ", x / (1 << 20));
    else if (x >= (1 << 10))
        cy += printf("%4lldK ", x / (1 << 10));
    else
        cy += printf("%4lldB ", x);

    string m_time = string(ctime(&sb.st_mtime));
    m_time = m_time.substr(4, 12);
    cy += printf(" %-12s ", m_time.c_str());

    if (isDirectory(abs_path))
        printf("%c[33m", 27);
    printf(" %-20s\n", dirName);
    if (isDirectory(abs_path))
        printf("%c[0m", 27);
    cy++;
}
