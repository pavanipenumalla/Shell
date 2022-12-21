#ifndef __HEADERS_H
#define __HEADERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <pwd.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>
#include <grp.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/utsname.h>
#include <wait.h>
#include <signal.h>

typedef long long int ll;
char home[500];
char username[50];
char prevdir[100];
int pid[1000];
char process[1000][100];
char pvthn[1000][100];
int check[1000];
int p_num[1000];
char hostname[100];
extern int c_pro;


#endif