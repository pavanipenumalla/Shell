#include "header.h"
void module_pwd(char **cmnd, int num)
{
     // absolute path
    char pd[100];
    getcwd(pd, sizeof(pd));
    printf("%s\n", pd);
}