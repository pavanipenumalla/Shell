#include "header.h"
void get_jobs(int fl)
{
    int n = 1000;
    char temp[1000];
    char temp1[1000];
    for (int i = 0; i < n - 1; i++)
    {
        int no_of_swaps = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            // printf("%d %d\n", i, j);
            if (strcasecmp(process[j],process[j + 1]) > 0)
            {
                strcpy(temp, process[j]);
                strcpy(process[j], process[j+1]);
                strcpy(process[j+1], temp);
                // printf("here2\n");
                int a = pid[j];
                pid[j] = pid[j+1];
                pid[j+1] = a;
                int b = check[j];
                check[j] = check[j+1];
                check[j+1] = b;
                int c = p_num[j];
                p_num[j] = p_num[j+1];
                p_num[j+1] = c;

                strcpy(temp1, pvthn[j]);
                strcpy(pvthn[j], pvthn[j+1]);
                strcpy(pvthn[j+1], temp1);
                no_of_swaps++;
                
            }
        }
        if(no_of_swaps==0)
        {
            break;
        }
    }

    for (int i = 0; i < 1000; i++)
    {
        if (pid[i] != 0)
        {
            if (check[i] != -1)
            {
                char p[100];
                char file[100];
                strcpy(file, "/proc/");
                sprintf(p, "%d", pid[i]);
                strcat(file, p);
                strcat(file, "/stat");

                FILE *fptr;
                fptr = fopen(file, "r");

                char state;
                fscanf(fptr, "%*d %*s %c", &state);
                fclose(fptr);
                char status[100];
                if (state == 'T')
                {
                    strcpy(status,"Stopped");
                }
                else
                {
                    strcpy(status,"Running");
                }
                if(fl==1)
                {
                    printf("[%d] %s %s [%d]\n",p_num[i],status,pvthn[i],pid[i]);
                }
                else if (fl == 2 && strcmp(status,"Running")==0)
                {
                    printf("[%d] %s %s [%d]\n",p_num[i],status,pvthn[i],pid[i]);
                }
                else if (fl == 3 && strcmp(status,"Stopped")==0)
                {
                    printf("[%d] %s %s [%d]\n",p_num[i],status,pvthn[i],pid[i]);
                }

            }
        }
    }
}