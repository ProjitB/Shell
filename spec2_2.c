#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int input_redir (char* argv, int length, char** res, char* input);
int output_redir (char* argv, int length, char** res, char* input);
//int input_output_redir (char* argv, int length, char** res);
int find_redir (char* argv, int length);

int input_redir (char* argv, int length, char** res, char* input)
{
    char* temp = strtok (argv, " ");
    int n = 0, i;
    //char** res = NULL;
    while (temp)
    {
        res = realloc (res, sizeof(char*) * (++n));
        if (res == NULL)
            exit(-1);
        res[n - 1] = temp;
        temp = strtok(NULL, " ");
    }
    res = realloc (res, sizeof(char*) * (n+1));
    res[n] = 0;
    int fd = open(input, O_RDONLY, 0);
    dup2(fd, STDIN_FILENO);
    close(fd);
    int status = execvp(res[0], res);
    if (!status)
        printf("The command could not be executed\n");
    return n;
}

int output_redir (char* argv, int length, char** res, char* output)
{
    char* temp = strtok (argv, " ");
    int n = 0, i;
    while (temp)
    {
        res = realloc(res, sizeof(char*) * (++n));
        if (res == NULL)
            exit(-1);
        res[n - 1] = temp;
        temp = strtok(NULL, " ");
    }
    res = realloc (res, sizeof(char*) * (n+1));
    res[n] = 0;
    int fd = creat(output, 0644);
    dup2(fd, STDOUT_FILENO);
    close (fd);
    //printf ("%s", output);
    int status  = execvp(res[0], res);
    if (!status)
        printf("The command could not be executed\n");
    return n;
}

int find_redir (char* argv, int length)
{
    int i = 0, flag = 0, j = 0, temp, n;
    printf ("%s\n", argv);
    char infile[50] = "", outfile[50] = "";
    char** res = NULL;
    //if flag == 0 -> nothing
    //if flag == 1 -> input_redir
    //if flag == 2 -> output _redir
    //if flag == 3 -> input_output_redir 
    while (i < length)
    {
        if (argv[i] == '<') //input redirection
        {
            if (flag == 0)
                flag = 1;
            else
                flag = 3;
            temp = i; //storing the value of i to continue the loop
            while (argv[i] != '>' || argv[i] != '\0' || argv[i] !='\n')
            {
                infile[j] = argv[temp];
                j++, temp++;
            }
            //now infile has the input filename, we hope
            i = temp;
        }
        if (argv[i] == '>')//output redirection
        {
            if (flag == 0)
                flag = 2;
            else
                flag = 3;
            temp = i+1;
            //printf("%d%c", temp, argv[temp]);
            //while (argv[temp] != '<' || argv[temp] != '\0' || argv[temp] != '\n' || temp < length)
            while (temp<length)
            {
                outfile[j] = argv[temp];
                j++, temp++;
            }
            
            printf("Outfile: %s", outfile);
            i = temp;
        }
        i++;
    }
    if (flag == 0)
        return -1;
    else if (flag == 1)
        n = input_redir(argv, length, res, infile);
    else if (flag == 2)
        n = output_redir(argv, length, res, outfile);
    //else
        //n = input_output_redir(argv, length, res, infile, outfile);
    return n;
}

int main()
{
    char input[1000];
    printf("<NAME@UBUNTU ~>");
    scanf("%s", input);
    ///printf("%s\n", input);
    int len = strlen(input);
    find_redir(input, len);
    return 0;
}
