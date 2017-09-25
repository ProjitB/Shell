#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int convert (char* num);

void pinfo(int pid)
{
    //int pid = getpid();
    char path[1025];
    char info[30];
    char op[1025];
    //printf("%d\n", pid);
    sprintf(path, "/proc/%d/status", pid);
    //printf("%s\n", path);
    FILE *fp;
    fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("pid does not exist\n");
        return;
    }
    printf ("pid:\t %d\n", pid);    
    int i = 0;
    while (fgets(info, 30, fp) != NULL)
    {
        if (i == 0 || i == 1 || i == 16)
            printf("%s", info);
        i++;
    }
    fclose(fp);

    return;
}

void findPid (char* argv, int length)
{
    if (length == 5)
        pinfo(getpid());
    else
    {
        char id[10];
        int i;
        for (i = 5; i <= length; i++)
            id[i-5] = argv[i];
        //int pid = convert(id);
        int pid = atoi(id);
        //printf("%d\n", pid);
        pinfo(pid);
    }

    return;
}

int convert (char* num)
{
    int len = strlen(num), dec = 0, i;

    for(i=0; i<len; i++)
        dec = dec * 10 + ( num[i] - '0' );
    return dec;
}
