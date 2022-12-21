#include "header.h"
void module_history(int c)
{
    char h_path[100];
    strcpy(h_path,home);
    strcat(h_path,"/h.txt");
    FILE *fp;
    fp = fopen(h_path,"r");
    
    if (c <= 10)
    {
        char t[100];
        while(fscanf(fp,"%[^\n]%*c",t)!=EOF)
        {
            printf("%s\n",t);
        }
    }
    else
    {
        int i = 0;
        char buffer[100][100];
        char t[100];
        while(fscanf(fp,"%[^\n]%*c",t)!=EOF)
        {
            strcpy(buffer[i++],t);
        }
        for (int i = c-10;i<c;i++)
        {
            printf("%s\n",buffer[i]);
        }
    }
    fclose(fp);

}