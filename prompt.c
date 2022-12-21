#include "header.h"
void prompt()
{
    char *path;
    char pwd[500];
    int len = strlen(home);
    if (getcwd(pwd, sizeof(pwd)) != NULL)
    {
        char *pointer = strstr(pwd, home);
        if (pointer != NULL)
        {
            path = pointer + len;
            printf("\033[0;36m");
            printf("<%s@%s:~%s>", username, hostname, path);
            printf("\033[0m");
        }
        else
        {
            path = pwd;
            printf("\033[0;36m");
            printf("<%s@%s:%s>", username, hostname, path);
            printf("\033[0m");
        }
    }
    else
    {
        perror("\033[0;31mError\033[0m");
    }
}
