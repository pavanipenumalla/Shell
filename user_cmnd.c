#include "header.h"
void exec_fg(char **cmnd, int j)
{
    if (j != 2)
    {
        printf("\033[0;31mIncorrect Arguments\033[0m");
        printf("\n");
    }
    int job_num = atoi(cmnd[1]);

    int flag = 0, index, p;
    char p_name[100];
    for (int i = 0; i < 1000; i++)
    {
        if (pid[i] != 0)
        {
            if (check[i] != -1)
            {
                if (p_num[i] == job_num)
                {
                    flag = 1;
                    index = i;
                    p = pid[i];
                    strcpy(p_name, process[i]);
                    break;
                }
            }
        }
    }

    if (flag == 0)
    {
        printf("\033[0;31mJob number not found\033[0m");
        printf("\n");
    }
    else
    {
        // printf("Process %s with pid %d continuing in foreground\n", p_name,p);
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(0, getpgid(p));
        kill(p, SIGCONT);
        int s;
        waitpid(p, &s, WUNTRACED);
        fflush(stdout);
        tcsetpgrp(0, getpid());
        signal(SIGTTOU, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);
        check[index] = -1;
        if(WIFSTOPPED(s))
        {
            printf("Process %s with pid %d stopped\n", p_name, p);
        }
    }
}

void exec_bg(char** cmnd,int j)
{
    if (j != 2)
    {
        printf("\033[0;31mIncorrect Arguments\033[0m");
        printf("\n");
    }
    int job_num = atoi(cmnd[1]);
    int flag = 0, index, p;
    char p_name[100];
    for (int i = 0; i < 1000; i++)
    {
        if (pid[i] != 0)
        {
            if (check[i] != -1)
            {
                if (p_num[i] == job_num)
                {
                    flag = 1;
                    index = i;
                    p = pid[i];
                    strcpy(p_name, process[i]);
                    break;
                }
            }
        }
    }

    if (flag == 0)
    {
        printf("Error : job number not found\n");
    }
    else
    {
        // printf("[%d] %s with pid %d running in background\n",job_num,p_name,p);
        if (kill(p,SIGCONT)<0)
        {
            perror("Error: \n");
        }
    }
}