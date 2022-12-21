#include "header.h"

void module_pinfo(char **cmnd, int num)
{
    int id;
    char pid[100];
    if (num == 1)
    {
        id = getpid();
        int a = sprintf(pid, "%d", id);
        if (a < 0)
        {
            perror("\033[0;31mError in copying\033[0m");
        }
    }
    else
    {
        strcpy(pid, cmnd[1]);
    }

    // All the details of the process are stored in /proc/pid/status file
    char file[100];
    strcpy(file, "/proc/");
    strcat(file, pid);
    strcat(file, "/stat");

    // opening the file
    FILE *fptr;
    fptr = fopen(file, "r");
    // The first field has process id
    fscanf(fptr, "%d", &id);
    // The second field has filename of the executable
    char file_exec[100];
    fscanf(fptr, "%s", file_exec);
    // The third field has the state of the process
    char state;
    fscanf(fptr, " %c", &state);
    int a,b;
    fscanf(fptr,"%*d %d %*d %*d %d",&a,&b);
    fclose(fptr);
    // Memory allocated to the program will be stored in /proc/pid/statm file
    char *pointer = strrchr(file, '/');
    char *st = file;
    char mem_file[100];
    if (pointer != NULL)
    {
        int i = 0;
        for (st; st <= pointer; st++)
        {
            mem_file[i] = file[i];
            i++;
        }
        mem_file[i] = '\0';
    }

    strcat(mem_file, "statm");
    // printf("%s\n",mem_file);
    ll mem;
    FILE *fp = fopen(mem_file, "r");
    fscanf(fp, "%lld", &mem);
    fclose(fp);

    // Executable path will be stored in /proc/pid/exe file
    char ex_file[100];
    strcpy(ex_file, "/proc/");
    strcat(ex_file, pid);
    strcat(ex_file, "/exe");
    // printf("%s\n",ex_file);
    char ex_path[100];
    readlink(ex_file, ex_path, sizeof(ex_path));
    char *path;
    int len = strlen(home);
    char *point = strstr(ex_path, home);
    char exec_file[100];
    strcpy(exec_file,"~");
    if (point != NULL)
    {
        path = point + len;
        strcat(exec_file,path);
    }
    else
    {
        strcat(exec_file,ex_path);
    }

    printf("pid : %s\n",pid);
    printf("process status : %c",state);
    if(a==b)
    {
        printf("+\n");
    }
    else
    {
        printf("\n");
    }
    printf("memory : %lld\n", mem);
    printf("executable path : %s\n", exec_file);
}