#include "header.h"
#include "cd.h"
#include "echo.h"
#include "ls.h"
#include "pwd.h"
#include "pinfo.h"
#include "history.h"
#include "sig.h"
#include "discover.h"
#include "fg.h"

void fbp(char *inp, int num, int *ani)
{
    char break_point1[] = "&";
    char break_point2[] = "' ','\t'";

    char *commands[500];
    char input[100];
    strcpy(input, inp);
    int l = strlen(input);
    // To break the given input into individual commands which are either ; or & separated
    int i = 0;
    int no_of_commands = 0;

    time_t t1, t2;

    char *cmd = strtok(inp, break_point1);
    while (cmd != NULL)
    {
        commands[i++] = cmd;
        cmd = strtok(NULL, break_point1);
        no_of_commands++;
    }
    int blu = 0;
    int ind = 0;
    while (no_of_commands >= 1)
    {
        char *cmnd[500];
        int j = 0;
        char *c;
        c = strtok(commands[blu], break_point2);
        while (c != NULL)
        {
            cmnd[j] = c;
            // printf("%s", cmnd[j]);
            c = strtok(NULL, break_point2);
            j++;
        }
        // strcpy(cmnd[j],"");
        cmnd[j] = NULL;

        if (no_of_commands > 1)
        {
            int ret = fork();
            if (ret == 0)
            {
                setpgid(0, 0);
                if (execvp(cmnd[0], cmnd) == -1)
                {
                    perror("\033[0;31mError\033[0m");
                    exit(0);
                }
            }
            else if (ret > 0)
            {
                int sr;
                setpgid(ret, 0);
                fprintf(stderr, "[%d] %d\n", *ani, ret);
                pid[ind] = ret;
                p_num[ind] = *ani;
                // printf("p_num %d ani %d\n", p_num[ind], *ani);
                strcpy(process[ind], cmnd[0]);
                strcpy(pvthn[ind], cmnd[0]);
                for (int u = 1; u < j; u++)
                {
                    strcat(pvthn[ind], " ");
                    strcat(pvthn[ind], cmnd[u]);
                }
                *ani = *ani + 1;

                ind++;
                setpgid(getpid(), 0);
                tcsetpgrp(0, getpgid(getpid()));
            }
            else
            {
                perror("\033[0;31mError\033[0m");
            }
        }
        else if (no_of_commands == 1)
        {
            if (input[l - 1] == '&')
            {
                int ret = fork();
                if (ret == 0)
                {
                    setpgid(0, 0);
                    if (execvp(cmnd[0], cmnd) == -1)
                    {
                       perror("\033[0;31mError\033[0m");
                        exit(0);
                    }
                }
                else if (ret > 0)
                {
                    
                    int sr;
                    setpgid(ret, 0);
                    fprintf(stderr, "[%d] %d\n", *ani, ret);
                    pid[ind] = ret;
                    p_num[ind] = *ani;
                    // printf("p_num %d ani %d\n", p_num[ind], *ani);
                    strcpy(process[ind], cmnd[0]);
                    strcpy(pvthn[ind], cmnd[0]);
                    for (int u = 1; u < j; u++)
                    {
                        strcat(pvthn[ind], " ");
                        strcat(pvthn[ind], cmnd[u]);
                    }
                    *ani = *ani + 1;

                    ind++;
                    // -------------------
                    setpgid(getpid(), 0);
                    tcsetpgrp(0, getpgid(getpid()));
                }
                else
                {
                    perror("\033[0;31mError\033[0m");
                }
            }
            else
            {
                t1 = time(0);

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
                else if (strcmp(cmnd[0], "sig") == 0)
                {
                    exec_sig(cmnd, j);
                }
                else if (strcmp(cmnd[0], "exit") == 0)
                {
                    exit(0);
                }
                else
                {
                    int urn = fork();
                    if (urn == 0)
                    {
                        setpgid(0, 0);
                        execvp(cmnd[0], cmnd);
                    }
                    else 
                    {
                         
                        setpgid(urn, 0);
                        signal(SIGTTIN, SIG_IGN);
                        signal(SIGTTOU, SIG_IGN);
                        tcsetpgrp(0, urn);
                        c_pro = urn;
                        int you;
                        //waitpid(urn, &you, WAIT_MYPGRP);
                        waitpid(urn, &you, WUNTRACED);
                        if (WIFSTOPPED(you))
                        {
                            pid[ind] = urn;
                            p_num[ind] = *ani;
                            // printf("p_num %d ani %d\n", p_num[ind], *ani);
                            strcpy(process[ind], cmnd[0]);
                            strcpy(pvthn[ind], cmnd[0]);
                            for (int u = 1; u < j; u++)
                            {
                                strcat(pvthn[ind], " ");
                                strcat(pvthn[ind], cmnd[u]);
                            }
                            *ani = *ani + 1;
                            ind++;
                            kill(urn, SIGSTOP);
                        }
                    }
                }
                c_pro = -1;
                t2 = time(0);
                int time_taken = t2 - t1;
                if (time_taken >= 1)
                {
                    fprintf(stderr, "%s took %d seconds to execute\n", cmnd[0], time_taken);
                }
                tcsetpgrp(0, getpgid(getpid()));
                signal(SIGTTIN, SIG_DFL);
                signal(SIGTTOU, SIG_DFL);
                ind++;
            }
        }
        blu++;
        no_of_commands--;
    }
}