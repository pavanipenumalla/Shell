#include "header.h"
#include "cd.h"
#include "echo.h"
#include "ls.h"
#include "pwd.h"
#include "pinfo.h"
#include "history.h"
#include "discover.h"
#include "io_redirect.h"
#include "fg.h"
#include "jobs.h"
void io_redirect(char *inp, int count)
{
    int cmnd_len = strlen(inp);
    char temp[1000];
    strcpy(temp, inp);
    int in = 0, out_wr = 0, out_ap = 0;
    for (int iter = 0; iter < cmnd_len; iter++)
    {
        if (out_ap == 0 && inp[iter] == '>')
        {
            out_wr = 1;
        }
        if (inp[iter] == '<')
        {
            in = 1;
        }
        if (inp[iter] == '>' && inp[iter + 1] == '>')
        {
            out_ap = 1;
            out_wr = 0;
        }
    }
    int both = 0;
    if ((out_wr == 1 || out_ap == 1) && in == 1)
    {
        both = 1;
    }
    int j;
    char break_point[] = "' ','\t'";

    char *cmnd[100];
    char *infile;
    char *outfile;
    char *l[2], *r[2];
    if (in == 1 && both == 0)
    {
        j = 0;
        char in_break[] = "<";
        for (int i = 0; i < 2; i++)
        {
            char *p;
            if (i == 0)
            {
                p = strtok(inp, in_break);
            }
            else
            {
                p = strtok(NULL, in_break);
            }

            l[i] = p;
        }
        char *c = strtok(l[0], break_point);
        while (c != NULL)
        {
            cmnd[j++] = c;
            c = strtok(NULL, break_point);
        }
        cmnd[j] = '\0';
        char *t;
        t = strtok(l[1], break_point);
        infile = t;
    }
    if ((out_wr == 1 || out_ap == 1) && both == 0)
    {
        j = 0;
        char out_break[] = ">";
        for (int i = 0; i < 2; i++)
        {
            char *g;
            if (i == 0)
            {
                g = strtok(inp, out_break);
            }
            else
            {
                g = strtok(NULL, out_break);
            }

            r[i] = g;
        }
        char *c = strtok(r[0], break_point);
        while (c != NULL)
        {
            cmnd[j++] = c;
            c = strtok(NULL, break_point);
        }
        cmnd[j] = '\0';
        char *t;
        t = strtok(r[1], break_point);
        outfile = t;
    }
    if (both == 1)
    {
        j = 0;
        char in_break[] = "<";
        for (int i = 0; i < 2; i++)
        {
            char *p;
            if (i == 0)
            {
                p = strtok(inp, in_break);
            }
            else
            {
                p = strtok(NULL, in_break);
            }

            l[i] = p;
        }
        char *c = strtok(l[0], break_point);
        while (c != NULL)
        {
            cmnd[j++] = c;
            c = strtok(NULL, break_point);
        }
        cmnd[j] = '\0';

        char out_break[] = ">";
        for (int i = 0; i < 2; i++)
        {
            char *g;
            if (i == 0)
            {
                g = strtok(l[1], out_break);
                
            }
            else
            {
                g = strtok(NULL, out_break);
                
            }

            r[i] = g;
        }
        infile = strtok(r[0], break_point);
        outfile = strtok(r[1], break_point);
    }

    int std_in = dup(0);
    int std_out = dup(1);
    // opening the files
    if (in == 1)
    {
        int in_desc = open(infile, O_RDONLY);
        if (in_desc > 0)
        {
            dup2(in_desc, 0);
        }
        else
        {
            perror("\033[0;31mError\033[0m");
        }
        close(in_desc);
    }

    if (out_wr == 1)
    {
        int out_desc = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_desc > 0)
        {
            dup2(out_desc, 1);
        }
        else
        {
            perror("\033[0;31mError\033[0m");
        }
        close(out_desc);
    }

    if (out_ap == 1)
    {
        int out_desc = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (out_desc > 0)
        {
            dup2(out_desc, 1);
        }
        else
        {
            perror("\033[0;31mError\033[0m");
        }
        close(out_desc);
    }

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
        module_history(count);
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
    dup2(std_in, 0);
    dup2(std_out, 1);
    close(std_in);
    close(std_out);
}