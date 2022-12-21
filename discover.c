#include "header.h"
int f = 0, g = 0;
void discover(char *cmnd, int num)
{
    // printf("cmnd %s\n",cmnd);
    struct stat dirr = {0};
    char path[500];
    char g[100];
    struct dirent *dir;
    DIR *d;

    getcwd(path, sizeof(path));
    if (strcmp(cmnd,"discover") == 0)
    {
        d = opendir(path);
        f = 1;
    }
    else if (strcmp(cmnd, ".") == 0)
    {
        d = opendir(path);
        f = 1;
    }
    else if (strcmp(cmnd, "~") == 0)
    {
        d = opendir(home);
        f = 2;
    }
    else
    {
        d = opendir(cmnd);
    }

    int l = strlen(home);

    if (d == NULL)
    {
        perror("\033[0;31mError\033[0m");
    }
    else
    {
        while ((dir = readdir(d)) != NULL)
        {
            char p[100];
            if (strcmp(cmnd, "discover") == 0)
            {
                strcpy(p, path);
                strcat(p, "/");
            }
            else if (strcmp(cmnd, ".") == 0)
            {
                strcpy(p, path);
                strcat(p, "/");
            }
            else if (strcmp(cmnd, "~") == 0)
            {
                strcpy(p, home);
                strcat(p, "/");
            }
            else
            {
                strcpy(p, cmnd);
                strcat(p, "/");
            }

            strcat(p, dir->d_name);
            if (num == 2 || num == 3)
            {
                if (stat(p, &dirr) == 0 && S_ISDIR(dirr.st_mode))
                {
                    char *pt;
                    char *pointer = strstr(p, home);
                    if (pointer != NULL)
                    {
                        pt = pointer + l;
                        int l1 = strlen(pt);
                        if (pt[l1 - 1] != '.' && (strcmp(cmnd, "~") == 0 || f == 2))
                        {
                            printf("~%s\n", pt);
                            discover(p, num);
                        }
                        else if (pt[l1 - 1] != '.')
                        {
                            printf(".%s\n", pt);
                            discover(p, num);
                        }
                    }
                    else if (strcmp("..", cmnd) == 0)
                    {
                        printf("%s\n", path);
                    }
                }
            }
            if (num == 1 || num == 3)
            {
                if (stat(p, &dirr) == 0 && S_ISREG(dirr.st_mode))
                {
                    char *pt;
                    char *pointer = strstr(p, home);
                    if (pointer != NULL)
                    {
                        pt = pointer + l;
                        int l1 = strlen(pt);
                        if (pt[l1 - 1] != '.' && (strcmp(cmnd, "~") == 0 || f == 2))
                        {
                            printf("~%s\n", pt);
                        }
                        else if (pt[l1 - 1] != '.')
                        {
                            printf(".%s\n", pt);
                        }
                    }
                    else
                    {
                        printf("%s\n", path);
                    }
                }
                else if (stat(p, &dirr) == 0 && S_ISDIR(dirr.st_mode))
                {
                    char *pt;
                    char *pointer = strstr(p, home);
                    if (pointer != NULL)
                    {
                        pt = pointer + l;
                        int l1 = strlen(pt);
                        if (pt[l1 - 1] != '.' && (strcmp(cmnd, "~") == 0 || f == 2))
                        {

                            discover(p, num);
                        }
                        else if (pt[l1 - 1] != '.')
                        {

                            discover(p, num);
                        }
                    }
                }
            }
        }
    }
    closedir(d);
}


void discover_prev(char *cmnd, int flag, char *prevdir)
{
    struct stat dirr = {0};
    char path[500];
    struct dirent *dir;
    DIR *d;
    if (strcmp("..", cmnd) == 0)
    {
        d = opendir("./..");
    }
    else
    {
        d = opendir(cmnd);
    }
    // printf("..\n");
    while ((dir = readdir(d)) != NULL)
    {
        if (flag == 2)
        {
            char g[100];
            if (strcmp("..", cmnd) == 0)
            {
                strcpy(path, prevdir);
                int len = strlen(prevdir);
                path[len - 1] = '\0';
            }
            else
            {
                strcpy(path, cmnd);
            }
            strcpy(g, path);
            strcat(g, "/");
            strcat(g, dir->d_name);

            if (stat(g, &dirr) == 0 && S_ISDIR(dirr.st_mode))
            {
                char temp_path[100];
                strcpy(temp_path, g);
                int len = strlen(prevdir);
                char temp_file[100];
                strcpy(temp_path, &temp_path[len]);
                int l1 = strlen(temp_path);
                if (temp_path[l1 - 1] != '.')
                {
                    printf("../%s\n", temp_path);
                    discover_prev(g, flag, prevdir);
                }
            }
        }
        else if (flag == 1)
        {
            char g[100];
            if (strcmp("..", cmnd) == 0)
            {
                strcpy(path, prevdir);
                int len = strlen(prevdir);
                path[len - 1] = '\0';
            }
            else
            {
                strcpy(path, cmnd);
            }
            strcpy(g, path);
            strcat(g, "/");
            strcat(g, dir->d_name);
            if (stat(g, &dirr) == 0 && S_ISREG(dirr.st_mode))
            {
                char temp_path[100];
                strcpy(temp_path, g);
                int len = strlen(prevdir);
                char temp_file[100];
                strcpy(temp_path, &temp_path[len]);
                int l1 = strlen(temp_path);
                if (temp_path[l1 - 1] != '.')
                {
                    printf("../%s\n", temp_path);
                }
            }
        }
        else if (flag == 3)
        {
            // printf("%s\n",prevdir);
            char g[100];
            if (strcmp("..", cmnd) == 0)
            {
                strcpy(path, prevdir);
                int len = strlen(prevdir);
                path[len - 1] = '\0';
            }
            else
            {
                strcpy(path, cmnd);
            }
            strcpy(g, path);
            strcat(g, "/");
            strcat(g, dir->d_name);

            if (stat(g, &dirr) == 0 && S_ISDIR(dirr.st_mode))
            {
                char temp_path[100];
                strcpy(temp_path, g);
                int len = strlen(prevdir);
                char temp_file[100];
                strcpy(temp_path, &temp_path[len]);
                int l1 = strlen(temp_path);
                if (temp_path[l1 - 1] != '.')
                {
                    printf("../%s\n", temp_path);
                    discover_prev(g, flag, prevdir);
                }
            }
            else
            {
                char temp_path[100];
                strcpy(temp_path, g);
                int len = strlen(prevdir);
                char temp_file[100];
                strcpy(temp_path, &temp_path[len]);
                int l1 = strlen(temp_path);
                if (temp_path[l1 - 1] != '.')
                {
                    printf("../%s\n", temp_path);
                }
            }
        }
    }
}
void discover_file(char *dire, char *file, char *prevdir)
{
    struct dirent *dir;
    DIR *d;
    struct stat dirr = {0};
    char path[500];
    char pav[100];
    getcwd(path, sizeof(path));

    if (strcmp(dire, ".") == 0)
    {
        d = opendir(path);
        strcpy(pav, path);
        g = 1;
    }
    else if (strcmp(dire, "~") == 0)
    {
        d = opendir(home);
        strcpy(pav, home);
        g = 2;
    }
    else if (strcmp(dire, "..") == 0)
    {
        d = opendir(prevdir);
        strcpy(pav, prevdir);
        g = 3;
    }
    else
    {
        d = opendir(dire);
        strcpy(pav, dire);
    }
    int y = strlen(pav);
    pav[y] = '\0';
    if (d == NULL)
    {
        perror("\033[0;31mError\033[0m");
    }
    else
    {
        while ((dir = readdir(d)) != NULL)
        {
            char temp_path[100];
            strcpy(temp_path, pav);
            strcat(temp_path, "/");
            strcat(temp_path, dir->d_name);
            // printf("temp_path:%s\n", temp_path);
            char f_name[100];
            strcpy(f_name, dir->d_name);
            if (stat(temp_path, &dirr) == 0)
            {
                if (S_ISREG(dirr.st_mode) && strcmp(file, f_name) == 0)
                {
                    int l1;
                    char temp_p[100];
                    if (g == 1)
                    {
                        printf(".");
                        strcpy(temp_p, temp_path);
                        int len = strlen(path);
                        strcpy(temp_p, &temp_p[len]);
                        l1 = strlen(temp_p);
                        temp_p[l1] = '\0';
                    }
                    else if (g == 2)
                    {
                        printf("~");
                        strcpy(temp_p, temp_path);
                        int len = strlen(home);
                        strcpy(temp_p, &temp_p[len]);
                        l1 = strlen(temp_p);
                        temp_p[l1] = '\0';
                    }
                    else if (g == 3)
                    {
                        printf("..");
                        strcpy(temp_p, temp_path);
                        int len = strlen(prevdir);
                        strcpy(temp_p, &temp_p[len]);
                        l1 = strlen(temp_p);
                        temp_p[l1] = '\0';
                    }
                    if (temp_p[l1 - 1] != '.')
                    {
                        printf("%s\n", temp_p);
                        return;
                    }
                }
                else if (S_ISDIR(dirr.st_mode))
                {
                    int x = strlen(temp_path);
                    if (temp_path[x - 1] != '.')
                    {
                        discover_file(temp_path, file, prevdir);
                    }
                }
            }
        }
    }
}
void discover_file_dir(char *dire, char *file)
{
    struct dirent *dir;
    DIR *d;
    struct stat dirr = {0};
    char pav[100];

    d = opendir(dire);
    strcpy(pav, dire);
    int y = strlen(pav);
    pav[y] = '\0';
    if (d == NULL)
    {
        perror("\033[0;31mError\033[0m");
    }
    else
    {
        while ((dir = readdir(d)) != NULL)
        {
            char temp_path[100];
            strcpy(temp_path, pav);
            strcat(temp_path, "/");
            strcat(temp_path, dir->d_name);
            // printf("temp_path:%s\n", temp_path);
            char f_name[100];
            strcpy(f_name, dir->d_name);
            if (stat(temp_path, &dirr) == 0)
            {
                if (S_ISREG(dirr.st_mode) && strcmp(file, f_name) == 0)
                {
                    int l1;
                    char temp_p[100];
                    printf(".");
                    strcpy(temp_p, temp_path);
                    int len = strlen(home);
                    strcpy(temp_p, &temp_p[len]);

                    l1 = strlen(temp_p);
                    temp_p[l1] = '\0';

                    if (temp_p[l1 - 1] != '.')
                    {
                        printf("%s\n", temp_p);
                    }
                }
                else if (S_ISDIR(dirr.st_mode))
                {
                    int x = strlen(temp_path);
                    if (temp_path[x - 1] != '.')
                    {
                        discover_file_dir(temp_path, file);
                    }
                }
            }
        }
    }
}
void discover_dir(char **cmnd, int num, int flag, char *prevdir)
{
    int file = 0;
    if ((cmnd[num - 1][0] = '"'))
    {
        file = 1;
    }
    if (file == 0)
    {
        for (int i = 1; i < num; i++)
        {
            if (strcmp("-f", cmnd[i]) != 0 && strcmp("-d", cmnd[i]) != 0)
            {
                char path[100];
                strcpy(path, home);
                char *pt;
                struct stat dirr = {0};
                if (cmnd[i][0] == '.' && cmnd[i][1] == '/')
                {
                    char *p = strchr(cmnd[i], 47);
                    strcat(path, p);
                    discover(path, flag);
                }
                else if (strcmp(cmnd[i], ".") == 0 || strcmp(cmnd[i], "~") == 0)
                {
                    discover(cmnd[i], flag);
                }
                else if (strcmp(cmnd[i], "..") == 0)
                {
                    // printf("pd d.c:%s\n",prevdir);
                    discover_prev(cmnd[i], flag, prevdir);
                }
                else
                {
                    char p[100];
                    strcpy(p, home);
                    strcat(p, "/");
                    strcat(p, cmnd[i]);
                    // printf("%s\n",p);
                    discover(p, flag);
                }
            }
        }
    }
    else if (file == 1)
    {
        char fil[100];
        int u = strlen(cmnd[num - 1]);
        int k = 0;
        for (int h = 1; h < u - 1; h++)
        {
            fil[k++] = cmnd[num - 1][h];
        }

        fil[k] = '\0';
        if (num > 2 && (strcmp(".", cmnd[1]) == 0) || (strcmp("..", cmnd[1]) == 0) || (strcmp("~", cmnd[1]) == 0))
        {
            discover_file(cmnd[1], fil, prevdir);
        }
        else if (num == 2)
        {
            discover_file(".", fil, prevdir);
        }
        else if (cmnd[1][0] == '.' && cmnd[1][1] == '/')
        {
            char path[100];
            strcpy(path, home);
            char *p = strchr(cmnd[1], 47);
            strcat(path, p);
            discover_file_dir(path, fil);
        }
        else
        {
            printf("%s\n", cmnd[1]);
            discover_file_dir(cmnd[1], fil);
        }
    }
}