#include "header.h"
void module_cd(char **cmnd, int num)
{
    if (num == 1)
    {
        chdir(home);
    }
    else if (strcmp(cmnd[1], "~") == 0)
    {
        chdir(home);
    }
    else if (strcmp(cmnd[1], ".") == 0)
        ;
    else if (strcmp(cmnd[1], "..") == 0)
    {
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
        chdir(dir);
    }
    else if (strcmp(cmnd[1], "-") == 0)
    {
        chdir(prevdir);
        printf("%s\n",prevdir);
    }
    else if ((cmnd[1][0]) == '~')
    {
        char st[100], t[100];
        strcpy(st, "/home/");
        strcat(st, username);
        int l = strlen(cmnd[1]);
        int i;
        for (i = 0; i < l - 1; i++)
        {
            t[i] = cmnd[1][i + 1];
        }
        t[l - 1] = '\0';
        strcat(st, t);
        // printf("%s\n", st);
        chdir(st);
    }
    else if (cmnd[1][0] == '.' && cmnd[1][1] == '/')
    {
        int le = strlen(cmnd[1]);
        printf("%d\n", le);
        char fe[100];
        int i, a = 0;
        for (i = 2; i < le; i++)
        {
            fe[i - 2] = cmnd[1][i];
            a++;
        }
        fe[a] = '\0';
        // printf("%s\n",fe);
        chdir(fe);
    }

    else if (cmnd[1][0] == '.' && cmnd[1][1] == '.')
    {
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
        chdir(dir);

        int le = strlen(cmnd[1]);
        printf("%d\n", le);
        char fe[100];
        int i, a = 0;
        for (i = 3; i < le; i++)
        {
            fe[i - 3] = cmnd[1][i];
            a++;
        }
        fe[a] = '\0';
        // printf("%s\n",fe);
        chdir(fe);
    }
    else if (chdir(cmnd[1]) != 0)
    {
        perror("\033[0;31mError\033[0m");
    }
    else
    {
        chdir(cmnd[1]);
    }
}