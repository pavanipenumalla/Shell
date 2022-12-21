#ifndef _DISCOVER_
#define _DISCOVER_
void discover(char *cmnd,int num);
void discover_dir(char **cmnd,int num,int flag,char* prevdir);
void discover_file(char *dire, char *file, char *prevdir);
void discover_file_dir(char *dire, char *file);
void discover_prev(char *cmnd, int flag, char *prevdir);
#endif