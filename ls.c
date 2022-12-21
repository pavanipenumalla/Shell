#include "header.h"
void module_ls(char **cmnd, int num, int flag)
{
    char *files[100];
    if (flag == 0 && (num == 1 || (num == 2 && strcmp(".", cmnd[1]) == 0)))
    {
        struct stat dirr = {0};
        char path[500];

        struct dirent *dir;
        DIR *d;
        d = opendir(".");
        int n = 0;
        if (d != NULL)
        {
            while ((dir = readdir(d)) != NULL)
            {
                if (dir->d_name[0] != '.')
                {
                    files[n++] = dir->d_name;
                }
            }
            closedir(d);
        }
        else
        {
            perror("\033[0;31mError\033[0m");
        }
        char *temp;
        // sorting the file names in alphabetical order
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (strcasecmp(files[j], files[j + 1]) > 0)
                {
                    temp = files[j];
                    files[j] = files[j + 1];
                    files[j + 1] = temp;
                }
            }
        }
        // printf("After sorting\n");
        for (int i = 0; i < n; i++)
        {
            getcwd(path, sizeof(path));
            strcat(path, "/");
            strcat(path, files[i]);
            if (stat(path, &dirr) == 0 && S_ISDIR(dirr.st_mode))
            {
                printf("\033[1;34m");
                printf("%s\n", files[i]);
                printf("\033[0m");
            }
            else if (stat(path, &dirr) == 0 && (dirr.st_mode & S_IXUSR))
            {
                printf("\033[1;32m");
                printf("%s\n", files[i]);
                printf("\033[0m");
            }
            else
            {
                printf("%s\n", files[i]);
            }
        }
        
    }

    else if (flag == 0 && num == 2 && strcmp("-a", cmnd[1]) == 0)
    {
        struct stat dirr = {0};
        char path[500];
        struct dirent *dir;
        DIR *d;
        d = opendir(".");
        int n = 0;
        if (d != NULL)
        {
            while ((dir = readdir(d)) != NULL)
            {
                files[n++] = dir->d_name;
            }
            closedir(d);
        }
        else
        {
            perror("\033[0;31mError\033[0m");
        }
        char *temp;

        // sorting the file names in alphabetical order
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (strcasecmp(files[j], files[j + 1]) > 0)
                {
                    temp = files[j];
                    files[j] = files[j + 1];
                    files[j + 1] = temp;
                }
            }
        }
        // printf("After sorting\n");
        for (int i = 0; i < n; i++)
        {
            getcwd(path, sizeof(path));
            strcat(path, "/");
            strcat(path, files[i]);
            if (stat(path, &dirr) == 0 && S_ISDIR(dirr.st_mode))
            {
                printf("\033[1;34m");
                printf("%s\n", files[i]);
                printf("\033[0m");
            }
            else if (stat(path, &dirr) == 0 && (dirr.st_mode & S_IXUSR))
            {
                printf("\033[1;32m");
                printf("%s\n", files[i]);
                printf("\033[0m");
            }
            else
            {
                printf("%s\n", files[i]);
            }
        }
    }
    else if (flag == 0 && num == 2 && strcmp("..", cmnd[1]) == 0)
    {
        struct stat dirr = {0};
        char path[500];
        struct dirent *dir;
        DIR *d;

        d = opendir("./..");
        int n = 0;
        if (d != NULL)
        {
            while ((dir = readdir(d)) != NULL)
            {
                if (dir->d_name[0] != '.')
                {
                    files[n++] = dir->d_name;
                }
            }
            closedir(d);
        }
        else
        {
            perror("\033[0;31mError\033[0m");
        }
        char *temp;

        // sorting the file names in alphabetical order

        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (strcasecmp(files[j], files[j + 1]) > 0)
                {
                    temp = files[j];
                    files[j] = files[j + 1];
                    files[j + 1] = temp;
                }
            }
        }
        // printf("After sorting\n");
        char start[100];
        getcwd(start, sizeof(start));
        char *pointer = strrchr(start, '/');
        char *s = start;
        char p_dir[100];
        if (pointer != NULL)
        {
            int i = 0;
            for (s; s <= pointer; s++)
            {
                p_dir[i] = start[i];
                i++;
            }
            p_dir[i] = '\0';
        }

        for (int i = 0; i < n; i++)
        {
            // getcwd(path, sizeof(path));
            strcpy(path, p_dir);
            // strcat(path, "/");
            strcat(path, files[i]);
            // printf("%s\n", path);
            if (stat(path, &dirr) == 0 && S_ISDIR(dirr.st_mode))
            {
                printf("\033[1;34m");
                printf("%s\n", files[i]);
                printf("\033[0m");
            }
            else if (stat(path, &dirr) == 0 && (dirr.st_mode & S_IXUSR))
            {
                printf("\033[1;32m");
                printf("%s\n", files[i]);
                printf("\033[0m");
            }
            else
            {
                printf("%s\n", files[i]);
            }
        }
    }
    else if (flag == 0 && num == 2 && strcmp("~", cmnd[1]) == 0)
    {
        struct dirent *dir;
        DIR *d;
         

        struct stat dirr = {0};
        char path[500];

        d = opendir(home);
        int n = 0;
        if (d != NULL)
        {
            while ((dir = readdir(d)) != NULL)
            {
                if (dir->d_name[0] != '.')
                {
                    files[n++] = dir->d_name;
                }
            }
            closedir(d);
        }
        else
        {
            perror("\033[0;31mError\033[0m");
        }

        /*for (int i = 0; i < n; i++)
        {
            printf("%s\n", files[i]);
        }*/
        char *temp;

        // sorting the file names in alphabetical order

        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (strcasecmp(files[j], files[j + 1]) > 0)
                {
                    temp = files[j];
                    files[j] = files[j + 1];
                    files[j + 1] = temp;
                }
            }
        }
        // printf("After sorting\n");
        for (int i = 0; i < n; i++)
        {
            strcpy(path, home);
            strcat(path, "/");
            strcat(path, files[i]);
            // printf("%s\n",path);
            if (stat(path, &dirr) == 0 && S_ISDIR(dirr.st_mode))
            {
                printf("\033[1;34m");
                printf("%s\n", files[i]);
                printf("\033[0m");
            }
            else if (stat(path, &dirr) == 0 && (dirr.st_mode & S_IXUSR))
            {
                printf("\033[1;32m");
                printf("%s\n", files[i]);
                printf("\033[0m");
            }
            else
            {
                printf("%s\n", files[i]);
            }
        }
    }
    else if (flag == 0 && num == 2 && strcmp("-l", cmnd[1]) == 0)
    {
        struct dirent *dir;
        DIR *d;
        d = opendir(".");

        ll bytes = 0;
        int n = 0;
        if (d != NULL)
        {
            while ((dir = readdir(d)) != NULL)
            {
                if (dir->d_name[0] != '.')
                {
                    files[n++] = dir->d_name;
                }
            }
        }
        char *temp;
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (strcasecmp(files[j], files[j + 1]) > 0)
                {
                    temp = files[j];
                    files[j] = files[j + 1];
                    files[j + 1] = temp;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            struct stat dirr = {0};
            char path[500];
            getcwd(path, sizeof(path));
            strcat(path, "/");
            strcat(path, files[i]);

            // for printing total bytes
            if (stat(path, &dirr) == 0)
            {
                bytes += dirr.st_blocks;
            }
        }
        if (bytes > 0)
            printf("total %lld\n", bytes / 2);

        for (int i = 0; i < n; i++)
        {
            struct stat dirr = {0};
            char path[500];
            getcwd(path, sizeof(path));
            strcat(path, "/");
            strcat(path, files[i]);
            char p[11];
            if (stat(path, &dirr) == 0)
            {
                // field - 1
                p[0] = S_ISDIR(dirr.st_mode) ? 'd' : '-';
                // field - 2  ->  owner permissions
                p[1] = (dirr.st_mode & S_IRUSR) ? 'r' : '-';
                p[2] = (dirr.st_mode & S_IWUSR) ? 'w' : '-';
                p[3] = (dirr.st_mode & S_IWUSR) ? 'x' : '-';
                // field - 3  ->  group permissions
                p[4] = (dirr.st_mode & S_IRGRP) ? 'r' : '-';
                p[5] = (dirr.st_mode & S_IWGRP) ? 'w' : '-';
                p[6] = (dirr.st_mode & S_IXGRP) ? 'x' : '-';
                // field - 4  ->  others permissions
                p[7] = (dirr.st_mode & S_IROTH) ? 'r' : '-';
                p[8] = (dirr.st_mode & S_IWOTH) ? 'w' : '-';
                p[9] = (dirr.st_mode & S_IXOTH) ? 'x' : '-';
                p[10] = '\0';

                // field - 5  -> no of links or directories inside
                int links = dirr.st_nlink;
                // field - 6  -> User that owns the file
                struct passwd *pass = getpwuid(dirr.st_uid);
                char *owner = pass->pw_name;
                // field - 7  -> Group that file belongs to
                struct group *grp = getgrgid(dirr.st_gid);
                char *group = grp->gr_name;
                // field - 8  -> Size in bytes
                ll size = dirr.st_size;
                // field - 9  -> Date of last modification
                char time[100];
                time_t t = dirr.st_mtime;
                struct tm l;
                localtime_r(&t, &l);
                strftime(time, sizeof time, "%b %d %Y %H:%M", &l);
                // field -10  -> Name of the file
                char *f = files[i];

                printf("%s  %d\t%s\t%s\t%lld\t%s  ", p, links, owner, group, size, time);
                if (stat(path, &dirr) == 0 && S_ISDIR(dirr.st_mode))
                {
                    printf("\033[1;34m");
                    printf("%s\n", files[i]);
                    printf("\033[0m");
                }
                else if (stat(path, &dirr) == 0 && (dirr.st_mode & S_IXUSR))
                {
                    printf("\033[1;32m");
                    printf("%s\n", files[i]);
                    printf("\033[0m");
                }
                else
                {
                    printf("%s\n", files[i]);
                }
            }
        }
        closedir(d);
    }

    // ls -a -l .. ls -al .. ls -la .. ls -l -a
    else if (flag == 0 && (num == 2 && ((strcmp("-al", cmnd[1]) == 0) || (strcmp("-la", cmnd[1]) == 0))) || (num == 3 && (((strcmp("-l", cmnd[1]) == 0) && (strcmp("-a", cmnd[2]) == 0)) || ((strcmp("-a", cmnd[1]) == 0) && (strcmp("-l", cmnd[2]) == 0)))))
    {
        struct dirent *dir;
        DIR *d;
        d = opendir(".");

        ll bytes = 0;
        int n = 0;
        if (d != NULL)
        {
            while ((dir = readdir(d)) != NULL)
            {
                files[n++] = dir->d_name;
            }
        }
        char *temp;
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (strcasecmp(files[j], files[j + 1]) > 0)
                {
                    temp = files[j];
                    files[j] = files[j + 1];
                    files[j + 1] = temp;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            struct stat dirr = {0};
            char path[500];
            getcwd(path, sizeof(path));
            strcat(path, "/");
            strcat(path, files[i]);

            // for printing total bytes
            if (stat(path, &dirr) == 0)
            {
                bytes += dirr.st_blocks;
            }
        }
        if (bytes > 0)
            printf("total %lld\n", bytes / 2);

        for (int i = 0; i < n; i++)
        {
            struct stat dirr = {0};
            char path[500];
            getcwd(path, sizeof(path));
            strcat(path, "/");
            strcat(path, files[i]);
            char p[11];
            if (stat(path, &dirr) == 0)
            {
                // field - 1
                p[0] = S_ISDIR(dirr.st_mode) ? 'd' : '-';
                // field - 2  ->  owner permissions
                p[1] = (dirr.st_mode & S_IRUSR) ? 'r' : '-';
                p[2] = (dirr.st_mode & S_IWUSR) ? 'w' : '-';
                p[3] = (dirr.st_mode & S_IWUSR) ? 'x' : '-';
                // field - 3  ->  group permissions
                p[4] = (dirr.st_mode & S_IRGRP) ? 'r' : '-';
                p[5] = (dirr.st_mode & S_IWGRP) ? 'w' : '-';
                p[6] = (dirr.st_mode & S_IXGRP) ? 'x' : '-';
                // field - 4  ->  others permissions
                p[7] = (dirr.st_mode & S_IROTH) ? 'r' : '-';
                p[8] = (dirr.st_mode & S_IWOTH) ? 'w' : '-';
                p[9] = (dirr.st_mode & S_IXOTH) ? 'x' : '-';
                p[10] = '\0';

                // field - 5  -> no of links or directories inside
                int links = dirr.st_nlink;
                // field - 6  -> User that owns the file
                struct passwd *pass = getpwuid(dirr.st_uid);
                char *owner = pass->pw_name;
                // field - 7  -> Group that file belongs to
                struct group *grp = getgrgid(dirr.st_gid);
                char *group = grp->gr_name;
                // field - 8  -> Size in bytes
                ll size = dirr.st_size;
                // field - 9  -> Date of last modification
                char time[100];
                time_t t = dirr.st_mtime;
                struct tm l;
                localtime_r(&t, &l);
                strftime(time, sizeof time, "%b %d %Y %H:%M", &l);
                // field -10  -> Name of the file
                char *f = files[i];

                printf("%s  %d\t%s\t%s\t%lld\t%s  ", p, links, owner, group, size, time);
                if (stat(path, &dirr) == 0 && S_ISDIR(dirr.st_mode))
                {
                    printf("\033[1;34m");
                    printf("%s\n", files[i]);
                    printf("\033[0m");
                }
                else if (stat(path, &dirr) == 0 && (dirr.st_mode & S_IXUSR))
                {
                    printf("\033[1;32m");
                    printf("%s\n", files[i]);
                    printf("\033[0m");
                }
                else
                {
                    printf("%s\n", files[i]);
                }
            }
        }
        closedir(d);
    }
    else if (num == 2 && flag == 0)
    {
        struct dirent *dir;
        DIR *d;

        struct stat dirr = {0};
        // printf("%s\n",path);
        char path[500];
        getcwd(path, sizeof(path));
        strcat(path, "/");
        strcat(path, cmnd[1]);
        if (stat(path, &dirr) == 0 && !S_ISDIR(dirr.st_mode))
        {
            printf("%s\n", cmnd[1]);
            return;
        }
        d = opendir(cmnd[1]);

        int n = 0;
        if (d != NULL)
        {
            while ((dir = readdir(d)) != NULL)
            {
                if (dir->d_name[0] != '.')
                {
                    files[n++] = dir->d_name;
                }
            }
            closedir(d);
        }
        else
        {
            perror("\033[0;31mError\033[0m");
        }
        char *temp;

        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (strcasecmp(files[j], files[j + 1]) > 0)
                {
                    temp = files[j];
                    files[j] = files[j + 1];
                    files[j + 1] = temp;
                }
            }
        }
        // printf("After sorting\n");
        for (int i = 0; i < n; i++)
        {
            struct stat dirr = {0};
            char path[500];
            getcwd(path, sizeof(path));
            strcat(path, "/");
            strcat(path, cmnd[1]);
            strcat(path, "/");
            strcat(path, files[i]);
            // printf("%s\n",path);
            if (stat(path, &dirr) == 0 && S_ISDIR(dirr.st_mode))
            {
                printf("\033[1;34m");
                printf("%s\n", files[i]);
                printf("\033[0m");
            }
            else if (stat(path, &dirr) == 0 && (dirr.st_mode & S_IXUSR))
            {
                printf("\033[1;32m");
                printf("%s\n", files[i]);
                printf("\033[0m");
            }
            else
            {
                printf("%s\n", files[i]);
            }
        }
    }
    else if (num == 2 && ((flag == 1 || flag == 3)))
    {
        struct dirent *dir;
        DIR *d;
        if (strcmp("~", cmnd[1]) == 0)
        {
            d = opendir(home);
        }
        else
        {
            d = opendir(cmnd[1]);
        }
        ll bytes = 0;
        int n = 0;
        if (d != NULL)
        {
            while ((dir = readdir(d)) != NULL)
            {
                if (flag == 1)
                {
                    if (dir->d_name[0] != '.')
                        files[n++] = dir->d_name;
                }
                else if (flag == 3)
                {
                    files[n++] = dir->d_name;
                }
            }
        }
        if (d == NULL)
        {
            files[0] = cmnd[1];
            n = 1;
        }
        char *temp;
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (strcasecmp(files[j], files[j + 1]) > 0)
                {
                    temp = files[j];
                    files[j] = files[j + 1];
                    files[j + 1] = temp;
                }
            }
        }
        int sr = 0;
        char path[500];
        for (int i = 0; i < n; i++)
        {
            struct stat dirr = {0};

            if (cmnd[1][0] == '/' && cmnd[1][1] == 'h')
            {
                sr = 1;
                strcpy(path, cmnd[1]);
            }
            else
            {
                getcwd(path, sizeof(path));
            }

            if (strcmp("~", cmnd[1]) != 0 && strcmp(".", cmnd[1]) != 0 && sr != 1)
            {
                strcat(path, "/");
                strcat(path, cmnd[1]);
                // printf("%s\n",path);
            }

            strcat(path, "/");
            strcat(path, files[i]);

            // printf("%s\n",path);
            // for printing total bytes
            if (stat(path, &dirr) == 0)
            {
                bytes += dirr.st_blocks;
            }
        }
        if (bytes > 0)
            printf("total %lld\n", bytes / 2);

        for (int i = 0; i < n; i++)
        {
            struct stat dirr = {0};
            // char path[500];
            if (cmnd[1][0] == '/' && cmnd[1][1] == 'h')
            {
                sr = 1;
                strcpy(path, cmnd[1]);
            }
            else
            {
                getcwd(path, sizeof(path));
            }

            if (strcmp("~", cmnd[1]) != 0 && strcmp(".", cmnd[1]) != 0 && sr != 1)
            {
                strcat(path, "/");
                strcat(path, cmnd[1]);
                // printf("%s\n",path);
            }

            // strcat(path, "/");
            // strcat(path, files[i]);
            if (d != NULL)
            {
                strcat(path, "/");
                strcat(path, files[i]);
            }
            char p[11];
            if (stat(path, &dirr) == 0)
            {
                // field - 1
                p[0] = S_ISDIR(dirr.st_mode) ? 'd' : '-';
                // field - 2  ->  owner permissions
                p[1] = (dirr.st_mode & S_IRUSR) ? 'r' : '-';
                p[2] = (dirr.st_mode & S_IWUSR) ? 'w' : '-';
                p[3] = (dirr.st_mode & S_IWUSR) ? 'x' : '-';
                // field - 3  ->  group permissions
                p[4] = (dirr.st_mode & S_IRGRP) ? 'r' : '-';
                p[5] = (dirr.st_mode & S_IWGRP) ? 'w' : '-';
                p[6] = (dirr.st_mode & S_IXGRP) ? 'x' : '-';
                // field - 4  ->  others permissions
                p[7] = (dirr.st_mode & S_IROTH) ? 'r' : '-';
                p[8] = (dirr.st_mode & S_IWOTH) ? 'w' : '-';
                p[9] = (dirr.st_mode & S_IXOTH) ? 'x' : '-';
                p[10] = '\0';

                // field - 5  -> no of links or directories inside
                int links = dirr.st_nlink;
                // field - 6  -> User that owns the file
                struct passwd *pass = getpwuid(dirr.st_uid);
                char *owner = pass->pw_name;
                // field - 7  -> Group that file belongs to
                struct group *grp = getgrgid(dirr.st_gid);
                char *group = grp->gr_name;
                // field - 8  -> Size in bytes
                ll size = dirr.st_size;
                // field - 9  -> Date of last modification
                char time[100];
                time_t t = dirr.st_mtime;
                struct tm l;
                localtime_r(&t, &l);
                strftime(time, sizeof time, "%b %d %Y %H:%M", &l);
                // field -10  -> Name of the file
                char *f = files[i];

                printf("%s  %d\t%s\t%s\t%lld\t%s  ", p, links, owner, group, size, time);
                if (stat(path, &dirr) == 0 && S_ISDIR(dirr.st_mode))
                {
                    printf("\033[1;34m");
                    printf("%s\n", files[i]);
                    printf("\033[0m");
                }
                else if (stat(path, &dirr) == 0 && (dirr.st_mode & S_IXUSR))
                {
                    printf("\033[1;32m");
                    printf("%s\n", files[i]);
                    printf("\033[0m");
                }
                else
                {
                    printf("%s\n", files[i]);
                }
            }
        }
        closedir(d);
    }
    else if (num == 2 && flag == 2)
    {
        struct dirent *dir;
        DIR *d;
        if (strcmp("~", cmnd[1]) == 0)
        {
            d = opendir(home);
        }
        else
        {
            d = opendir(cmnd[1]);
        }
        int n = 0;
        if (d != NULL)
        {
            while ((dir = readdir(d)) != NULL)
            {
                files[n++] = dir->d_name;
            }
            closedir(d);
        }
        if (d == NULL)
        {
            files[0] = cmnd[1];
            n = 1;
        }
        char *temp;

        // sorting the file names in alphabetical order
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (strcasecmp(files[j], files[j + 1]) > 0)
                {
                    temp = files[j];
                    files[j] = files[j + 1];
                    files[j + 1] = temp;
                }
            }
        }
        // printf("After sorting\n");
        for (int i = 0; i < n; i++)
        {
            struct stat dirr = {0};
            char path[500];
            int sr=0;
            if (cmnd[1][0] == '/' && cmnd[1][1] == 'h')
            {
                sr = 1;
                strcpy(path, cmnd[1]);
            }
            else
            {
                getcwd(path, sizeof(path));
            }

            if (strcmp("~", cmnd[1]) != 0 && strcmp(".", cmnd[1]) != 0 && sr != 1)
            {
                strcat(path, "/");
                strcat(path, cmnd[1]);
                // printf("%s\n",path);
            }
            strcat(path, "/");
            strcat(path, files[i]);
            if (stat(path, &dirr) == 0 && S_ISDIR(dirr.st_mode))
            {
                printf("\033[1;34m");
                printf("%s\n", files[i]);
                printf("\033[0m");
            }
            else if (stat(path, &dirr) == 0 && (dirr.st_mode & S_IXUSR))
            {
                printf("\033[1;32m");
                printf("%s\n", files[i]);
                printf("\033[0m");
            }
            else
            {
                printf("%s\n", files[i]);
            }
        }
    }
}