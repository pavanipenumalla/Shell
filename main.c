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
#include "user_cmnd.h"
#include "sig.h"
#include "pipe.h"
#include "prompt.h"

#define MAX_HIST_RANGE 20
int fg = 0;
int shr = 1;
int c_pro = -1;

void exec_c(int s)
{
    if (c_pro != -1)
    {
        kill(c_pro,SIGINT);
    }
    printf("\n");
    prompt();
    fflush(stdout);
    return;
}

void exec_z(int s)
{
    printf("\n");
    prompt(); 
    fflush(stdout);
    return;
}

int main()
{
    // Handling signals
    signal(SIGINT,exec_c); // ctrl^c
    signal(SIGTSTP,exec_z);

    memset(pid, 0, sizeof(pid));
    memset(check, 0, sizeof(check));
    // p_num = mmap(NULL, sizeof *p_num, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    // To get the username
    struct passwd *name;
    name = getpwuid(getuid());
    strcpy(username, name->pw_name);
    // printf("%s@",username);

    // To get the hostname

    gethostname(hostname, HOST_NAME_MAX + 1);
    // printf("%s",hostname);

    // To get the current working directory, which will be the home for shell
    getcwd(home, sizeof(home));
    // printf("home : %s\n",home);
    int len = strlen(home);

    char *path;
    char pwd[500];

    // To get the history
    char history[500][1000];
    char hist_path[100];
    strcpy(hist_path, home);
    strcat(hist_path, "/h.txt");

    FILE *fh;
    fh = fopen(hist_path, "a+");
    fclose(fh);
    int h = 0;
    if (fh = fopen(hist_path, "r"))
    {

        char temp[100];
        while (fscanf(fh, "%[^\n]%*c", temp) != EOF)
        {
            strcpy(history[h++], temp);
        }
        fclose(fh);
    }
    int h_count = h;
    // printf("%d\n", h_count);

    char break_point1[] = ";";        // break points to break the given input into different commands
    char break_point2[] = "' ','\t'"; // break points to break the command into different parts
P:
    while (1)
    {
        pid_t pi;
        int st;
        int store;
        while ((pi = waitpid(-1, &st, WNOHANG)) > 0)
        {
            for (int sep = 0; sep < 1000; sep++)
            {
                // printf("%d\n",pid[sep]);
                if (pid[sep] == pi)
                {
                    store = sep;
                    break;
                }
            }
            check[store] = -1;
            if (WIFEXITED(st))
            {
                fprintf(stderr, "%s process with pid %d exited normally\n", process[store], pi);
            }
            else
            {
                fprintf(stderr, "%s process with pid %d exited abnormally\n", process[store], pi);
            }
            shr--;
        }

        strcpy(prevdir, pwd);
         
        prompt();
        char input[500];
        // handling ctrl^d
        if (scanf("%[^\n]%*c", input) == EOF)
        {
            printf("\n");
            return 0;
        }
        char *commands[500];

        // To break the given input into individual commands which are either ; or & separated
        int i = 0;
        int no_of_commands = 0;
        char *cmd = strtok(input, break_point1);
        while (cmd != NULL)
        {
            commands[i++] = cmd;
            cmd = strtok(NULL, break_point1);
            no_of_commands++;
        }
        // storing the commands in h.txt file
        for (int k = 0; k < no_of_commands; k++)
        {
            if (h_count == 0)
            {
                strcpy(history[k], commands[k]);
                h_count++;
            }
            else if (h_count < 20)
            {
                if (strcmp(history[h_count - 1], commands[k]) != 0)
                {
                    strcpy(history[h_count], commands[k]);
                    h_count++;
                }
            }
            else
            {
                if (strcmp(history[h_count - 1], commands[k]) != 0)
                {
                    int i = 0;
                    while (i < MAX_HIST_RANGE - 1)
                    {
                        strcpy(history[i], history[i + 1]);
                        i++;
                    }
                    strcpy(history[19], commands[k]);
                    h_count = MAX_HIST_RANGE;
                }
            }
        }

        int count = 0;
        FILE *hist_file;
        hist_file = fopen(hist_path, "w");
        for (int i = 0; i < h_count; i++)
        {
            fprintf(hist_file, "%s\n", history[i]);
            count++;
        }
        fclose(hist_file);

        int siya = 0;
        while (no_of_commands--)
        {
            int p_flag = 0,io_flag = 0;
            int j = 0;
            char *cmnd[500];
            char red[1000];
            strcpy(red, commands[siya]);
            int cmnd_len = strlen(red);
            int m = 0;
            for (int iter = 0; iter < cmnd_len; iter++)
            {
                if (red[iter] == '>' || red[iter] == '<')
                {
                    m = 1;
                    io_flag = 1; 
                    // io_redirect(red, count);
                }
                if (red[iter] == '|')
                {
                    m = 1;
                    p_flag = 1;
                }
            }
            if (m==1 )
            {
                if (p_flag == 1)
                {
                    exec_pipe(red,count);
                }
                else if (io_flag==1)
                {
                    io_redirect(red,count);
                }
            }
            if (m == 0)
            {
                char *c = strtok(commands[siya], break_point2);
                while (c != NULL)
                {
                    cmnd[j++] = c;
                    c = strtok(NULL, break_point2);
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
                        goto P;
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
                else if (strcmp(cmnd[0],"sig")==0)
                {
                    exec_sig(cmnd,j);
                }
                else if (strcmp(cmnd[0],"fg")==0)
                {
                    exec_fg(cmnd,j);
                }
                else if (strcmp(cmnd[0],"bg")==0)
                {
                    exec_bg(cmnd,j);
                }
                else
                {
                    fbp(red, j, &shr);
                }
            }
            siya++;
        }
    }
    return 0;
}