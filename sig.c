#include "header.h"
void exec_sig(char** cmnd,int j)
{
    if(j!=3)
    {
        printf("\033[0;31mIncorrect Arguments\033[0m");
        printf("\n");
        exit(0);
    }
    int job_num = atoi(cmnd[1]);
    int sig_num = atoi(cmnd[2]);

    int index,flag = 0,p;
    for (int i = 0;i<1000;i++)
    {
        if (pid[i]!=0)
        {
            if(check[i]!=-1)
            {
                if (p_num[i]== job_num)
                {
                    flag = 1;
                    index = i;
                    p = pid[i];
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
    else if(flag == 1)
    {
        int k = kill(p,sig_num);
        if (k<0)
        {
            perror("\033[0;31mError in sig\033[0m");
        }
    }
}