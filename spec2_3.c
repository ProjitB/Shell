#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int commands (char* arg, int length);
int piping (char** argv, int argc);

int commands (char* arg, int length)
{
    int n = 0, i = 0;
    char** argv = NULL;
    char* temp = strtok (arg, "|");
    while (temp)
    {
        argv  = realloc(argv, sizeof(char*) * (++n));
        if (!argv)
            exit(-1);
        argv[n-1] = temp;
        temp = strtok (NULL, "|");
    }
    int status = piping (argv, n);
    return status;
}

int piping (char** argv, int argc)
{
    int i;
    for (i = 1; i < argc-1; i++)
    {
        int pd[2];
        pipe(pd);
        if (!fork())
        {
            dup2(pd[i], i);
            int status = execlp(argv[i], argv[i], NULL);
            if (!status) printf("Could not execute \'%s\'\n", argv[i]);
        }
        dup2(pd[0], 0);
        close(pd[1]);
    }
    int status = execlp(argv[i], argv[i], NULL);
    if (!status) printf("Could not execuute \'%s\'\n", argv[i]);

    return status;
}

int main ()
{
    char input[] = "ls -al | wc";
    commands (input, strlen(input));
    return 0;
}
