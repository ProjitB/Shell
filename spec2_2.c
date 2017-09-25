#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include "spec4.c"
#include <string.h>
#include <fcntl.h>

int find_redir (char* argv, int length);
int input_redir (char* argv, int length);
int output_redir (char* argv, int length);
int input_output_redir (char* argv, int length);

int find_redir (char* argv, int length)
{
    int flag = 0, i, n;
    //char** result = NULL;
    for (i = 0; i < length; i++)
    {
        if (argv[i] == '<' && flag == 0)
            flag = 1;
        if (argv[i] == '>' && flag == 0)
            flag = 2;
        if ((argv[i] == '<' || argv[i] == '>') && flag > 0)
            flag = 3;
    }
    if (!flag)
        return 0;
    else if (flag == 1)
        n = input_redir (argv, length);
    else if (flag == 2)
        n = output_redir (argv, length);
    else
        n = input_output_redir (argv, length);

    return n;
}

int output_redir (char* arg, int length)
{
    int i = 0, j = 0;
    char output[500] = "", cmd[500] = "";
    //printf ("%s\n", arg);
    //printf("%c\n", arg[5]);
    while (arg[i] != 62)
    {
        cmd[i] = arg[i];
        i++;
    }
    cmd [i-1] = '\0';
    printf("%s", cmd);
    //i has the character ">" in it. Now, it needs i+2
    i = i + 2;
    while (i < length)
    {
        output[j] = arg[i];
        i++, j++;
    }
    //printf ("%s\n", output);
    int fd = open (output, O_CREAT, O_WRONLY);
    dup2 (fd, STDOUT_FILENO);
    //close(fd);
    char** result = NULL;
    
    convert_Token (cmd, result);
    close (fd);
    return 2;
}


int input_redir (char* arg, int length)
{
    int i = 0, j = 0;
    char input[500] = "";
    //printf ("%s\n", arg);
    while (arg[i] != 60) i++;
    //printf("%s\n", cmd);
    i = i + 2;
    while (i < length)
    {
        input[j] = arg[i];
        i++, j++;
    }
    //strcat(strcat(cmd, " "), input);
    //printf ("%s\n", input);
    //printf("%s\n", cmd);
    int fd = open (input, O_RDONLY);
    dup2 (fd, STDIN_FILENO);
    close(fd);
    char** result = NULL;
    convert_Token(arg, result);
    //close(fd);
    return 1;
}

int input_output_redir (char* arg, int length)
{
    int i = 0, j = 0, f1 = 0, f2 = 0;
    //arg is of form command > op < ip
    //or command < ip > op
    char cmd[500] = "", input[500] = "", output[500] = "";
    while (arg[i] != 60 && arg[i] != 62)
    {
        cmd[i] = arg[i];
        i++;
    }
    //i  = i + 2;
    if (arg[i] == 60)
    {
        i = i + 2;
        while (arg[i] != 62)
        {
            input[j] = arg[i];
            i++, j++;
        }
        j = 0;
        i = i + 2;
        while (i < length)
        {
            output[j] = arg[i];
            i++, j++;
        }
    }
    else if (arg[i] == 62)
    {
        while (arg[i] != 60)
        {
            output[j] = arg[i];
            i++, j++;
        }
        j = 0;
        i = i + 2;
        while (i < length)
        {
            input[j] = arg[i];
            i++, j++;
        }
    }
    //printf("%s\n%s\n%s\n", cmd, input, output);
    strcat(strcat(cmd, " "), input);
    int fd1 = open (input, O_RDONLY, 0);
    dup2(fd1, STDIN_FILENO);
    close(fd1);
    int fd2 = creat (output, 0644);
    dup2(fd2, STDOUT_FILENO);
    char** result = NULL;
    convert_Token(cmd, result);
    close (fd2);
}

int main()
{
    
    char inputString[] = "more < /etc/passwd > pwd.txt";
    find_redir (inputString, strlen(inputString));
    return 0;
}
