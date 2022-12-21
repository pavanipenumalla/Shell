#include "header.h"
#include "cd.h"
#include "echo.h"
#include "ls.h"
#include "pwd.h"
#include "pinfo.h"
#include "io_redirect.h"
#include "jobs.h"
#include "history.h"
#include "discover.h"
#include "sig.h"
#include "user_cmnd.h"
#include "fg.h"
void execute(char *command, int cnt)
{
    char *cmnd[100];
    char bp2[] = "' ','\t'";
    char *t = command;
    char *c = strtok(command, bp2);
    int j = 0;
    while (c != NULL)
    {
        cmnd[j++] = c;
        c = strtok(NULL, bp2);
    }
    cmnd[j] = NULL;
    if (strcmp(cmnd[0], "cd") == 0)
    {
        module_cd(cmnd, j);
    }
    else if (strcmp(cmnd[0], "echo") == 0)
    {
        module_echo(cmnd, j);
    }
    else if (strcmp(cmnd[0], "pwd") == 0)
    {
        module_pwd(cmnd, j);
    }
    else if (strcmp(cmnd[0], "ls") == 0)
    {
        int flag = 0, flag1 = 0, flag2 = 0, f = 0, count = j;
        if (j <= 2)
            module_ls(cmnd, j, flag);
        else if (j == 3 && (((strcmp("-l", cmnd[1]) == 0) && (strcmp("-a", cmnd[2]) == 0)) || ((strcmp("-a", cmnd[1]) == 0) && (strcmp("-l", cmnd[2]) == 0))))
        {
            module_ls(cmnd, j, flag);
        }
        else if (j > 3)
        {
            for (int i = 1; i < j; i++)
            {
                if (strcmp("-l", cmnd[i]) == 0 || strcmp("-a", cmnd[i]) == 0 || strcmp("-la", cmnd[i]) == 0 || strcmp("-al", cmnd[i]) == 0)
                {
                    f = 1;
                    count -= 1;
                }
            }
        }
    L:
        if (f == 1 && j > 2)
        {
            for (int i = 1; i < j; i++)
            {
                if (strcmp("-l", cmnd[i]) == 0)
                {
                    flag = 1;
                    flag1 = 1;
                }
                else if (strcmp("-a", cmnd[i]) == 0)
                {
                    flag = 2;
                    flag2 = 1;
                }
                else if (strcmp("-la", cmnd[i]) == 0 || strcmp("-al", cmnd[i]) == 0)
                {
                    flag = 3;
                }
            }
            if (flag1 == 1 && flag2 == 1)
            {
                flag = 3;
            }
            for (int i = 1; i < j; i++)
            {
                char *t_cmnd[2];
                t_cmnd[0] = "ls";
                if (strcmp("-l", cmnd[i]) != 0 && strcmp("-a", cmnd[i]) != 0 && strcmp("-la", cmnd[i]) != 0 && strcmp("-al", cmnd[i]) != 0)
                {
                    t_cmnd[1] = cmnd[i];
                    if (count > 2)
                    {
                        printf("%s:\n", cmnd[i]);
                    }
                    module_ls(t_cmnd, 2, flag);
                    printf("\n");
                }
            }
        }

        if (f != 1 && j > 2)
        {
            for (int i = 1; i < j; i++)
            {
                char *t_cmnd[2];
                t_cmnd[0] = "ls";

                t_cmnd[1] = cmnd[i];
                if (count > 2)
                {
                    printf("%s:\n", cmnd[i]);
                }
                module_ls(t_cmnd, 2, flag);
                printf("\n");
            }
        }
    }
    else if (strcmp(cmnd[0], "pinfo") == 0)
    {
        module_pinfo(cmnd, j);
    }
    else if (strcmp(cmnd[0], "history") == 0)
    {
        module_history(cnt);
    }
    else if (strcmp(cmnd[0], "discover") == 0)
    {
        int f = 0;
        if (j == 1)
        {
            f = 3;
        }
        else if (j == 2)
        {
            if (strcmp(cmnd[1], "-f") == 0)
                f = 1;
            else if (strcmp(cmnd[1], "-d") == 0)
                f = 2;
        }
        else if (j == 3 && (((strcmp("-f", cmnd[1]) == 0) && (strcmp("-d", cmnd[2]) == 0)) || ((strcmp("-d", cmnd[1]) == 0) && (strcmp("-f", cmnd[2]) == 0))))
        {
            f = 3;
        }
        if (f)
        {
            discover(cmnd[0], f);
        }
        else
        {
            int flag = 3, fl1 = 0, fl2 = 0;
            for (int k = 0; k < j; k++)
            {
                if (strcmp(cmnd[k], "-f") == 0)
                {
                    fl1 = 1;
                    flag = 1;
                }
                else if (strcmp(cmnd[k], "-d") == 0)
                {
                    fl2 = 1;
                    flag = 2;
                }
            }
            if (flag == 0 || (fl1 == 1 && fl2 == 1))
            {
                flag = 3;
            }
            char start[100];
            getcwd(start, sizeof(start));
            char *pointer = strrchr(start, '/');
            char *s = start;
            char dir[100];
            if (pointer != NULL)
            {
                int i = 0;
                for (s; s <= pointer; s++)
                {
                    dir[i] = start[i];
                    i++;
                }
                dir[i] = '\0';
            }
            discover_dir(cmnd, j, flag, dir);
        }
    }
    else if (strcmp(cmnd[0], "exit") == 0)
    {
        exit(0);
    }
    else if (strcmp(cmnd[0], "jobs") == 0)
    {
        int fl = 0;
        if (j == 1)
        {
            fl = 1;
        }
        else if (j == 2 && strcmp(cmnd[1], "-r") == 0)
        {
            fl = 2;
        }
        else if (j == 2 && strcmp(cmnd[1], "-s") == 0)
        {
            fl = 3;
        }
        get_jobs(fl);
    }
    else if (strcmp(cmnd[0], "sig") == 0)
    {
        exec_sig(cmnd, j);
    }
    else if (strcmp(cmnd[0], "fg") == 0)
    {
        exec_fg(cmnd, j);
    }
    else if (strcmp(cmnd[0], "bg") == 0)
    {
        exec_bg(cmnd, j);
    }
    else
    {
        int ret = fork();
        if (ret == 0)
        {
            if (execvp(cmnd[0], cmnd) == -1)
            {
              perror("\033[0;31mError\033[0m");
                exit(0);
            }
        }
        else if (ret > 0)
        {
            wait(NULL);
        }
        else
        {
            perror("\033[0;31mError\033[0m");
        }
    }
}