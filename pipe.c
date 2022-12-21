#include "header.h"
#include "cd.h"
#include "echo.h"
#include "ls.h"
#include "pwd.h"
#include "commands.h"
#include "pinfo.h"
#include "io_redirect.h"
#include "jobs.h"
#include "history.h"
#include "discover.h"
#include "fg.h"
void run_command(char *command, int cnt)
{
    int m = 0;
    int cmnd_len = strlen(command);
    for (int iter = 0; iter < cmnd_len; iter++)
    {
        if (command[iter] == '>' || command[iter] == '<')
        {
            m = 1;
            io_redirect(command, cnt);
        }
    }
    if (m == 0)
    {
        execute(command,cnt);
    }
}

void exec_pipe(char *inp, int cnt)
{
    int i = 0;
    char *p_commands[100];
    int commands = 0;
    char break_point1[] = "|";
    char *cmd = strtok(inp, break_point1);
    while (cmd != NULL)
    {
        p_commands[i++] = cmd;
        cmd = strtok(NULL, break_point1);
        commands++;
    }
    p_commands[i] = NULL;
    int std_in = dup(0);
    int std_out = dup(1);

    int pipe_arr[2][2];
    pipe(pipe_arr[0]); // pipe_arr[0][0] -> file descriptor for the read end of pipe.
                       // pipe_arr[0][1] -> file descriptor for the write end of pipe.
    int g = dup2(pipe_arr[0][1], 1);
    if (g < 0)
    {
        perror("\033[0;31mError in dup2\033[0m");
    }
    run_command(p_commands[0], cnt);
    commands--;
    close(pipe_arr[0][1]);

    int j = 1;
    while (commands > 1)
    {
        int p = pipe(pipe_arr[j]);
        if (p == 0)
        {
            int q = dup2(pipe_arr[j - 1][0], 0);
            if (q < 0)
            {
                perror("\033[0;31mError in dup2\033[0m");
            }
            int r = dup2(pipe_arr[j][1], 1);
            if (r < 0)
            {
                perror("\033[0;31mError in dup2\033[0m");
            }
            run_command(p_commands[j], cnt);
            close(pipe_arr[j - 1][0]);
            close(pipe_arr[j][1]);
        }
        else
        {
            perror("\033[0;31mError in pipe command\033[0m");
        }
        j++;
        commands--;
    }
    int x = dup2(pipe_arr[j - 1][0], 0);
    if (x < 0)
    {
        perror("\033[0;31mError in dup2\033[0m");
    }
    int y = dup2(std_out, 1);
    if (y < 0)
    {
        perror("\033[0;31mError in dup2\033[0m");
    }
    run_command(p_commands[j], cnt);
    int z = dup2(std_in, 0);
    if (z < 0)
    {
        perror("\033[0;31mError in dup2\033[0m");
    }
    close(pipe_arr[j - 1][0]);
    close(std_in);
    close(std_out);
}