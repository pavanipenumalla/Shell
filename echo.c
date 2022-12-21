#include "header.h"
void module_echo(char **cmnd, int num)
{
    int i = 1;
    while (i < num)
    {
        printf("%s ", cmnd[i++]);
    }
    printf("\n");
}