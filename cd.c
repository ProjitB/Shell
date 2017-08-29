#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <string.h>

void removeDir (char* pres);
void addDir(char* pres, char* dir);

int err;

int cd (char* arg)
{
    int size = strlen(arg);
    char pwd[1025], nwd[1025], path[1025], token[1025];
    char a[2] = "/"; 
    //pwd = the present working directory where cd was called
    //nwd = the next working directory where the cd will take the terminal
    
    getcwd(pwd, sizeof(pwd));
    int i = 3; // the initial part of the string is always cd, so this need not be checked
    
    while (i < size)
    {
        if (arg[i] == '\0')
            break;
        path[i-3] = arg[i];
        i++;
    }

    int len = strlen(pwd);
    int err; 
    printf("%s", path);

    if (path[0] == '/')
    {
        //absolute path
        err = chdir (path);
    }
    
    else 
    {
        /* There are three cases to be handled here:
         * Case with ~ beginning markers
         * Case with ../../x
         * Case with relative path
         * This is being handled from / to /
         */

        int j = 0;
        char* token = strtok(path, a); //This is the list of all the entries 
        //strcat(pwd, "/");
        while (token != NULL)
        {
            printf("%s\n", token);
            /*if (!strcmp(token, ".."))
                removeDir(pwd);
            else
            {
                strcat(pwd, "/");
                addDir(pwd, token);
            }*/
            token = strtok(NULL, a);
            //printf("%s \n", token);
        }
    }
    
    //if (!err)
    //printf("\n2. bash: cd: %s:", path);
    return err;
}
char dir[1025];

void removeDir (char* pres)
{
    int len  = strlen(pres);
    //char dir[1025];
    while (pres[len-1] != '/')
        len--;
    int i = 0;
    while (i < len)
    {
        dir[i] = pres[i];
        i++;
    }
    chdir (dir);
    printf("%s", dir);
}

void addDir (char* pres, char* dir)
{
    int len = strlen(pres);
    //strcat (pres, "/");
    strcat(pres, dir);
    //int cmp = strcmp (pres, "/home/alok/Shell/test1");
    //int s = strlen(pres);
    pres[strlen(pres)-1] = '\0';
    printf("%s\n", pres);
    //int cmp = strcmp (pres, "/home/alok/Shell/test1");
    chdir(pres);
    pres[strlen(pres)] = '/';
    printf("%s\n", pres);
}
