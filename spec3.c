#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

void noflagls (char* argv, int length);
void bothflagsls (char* argv, int length);
void lsl (char* argv, int length);
void lsa (char* argv, int length);

DIR *mydir;
struct dirent *myfile;
struct stat mystat;
char path[1025];
int length;

void findPath (char* argv, int length, int rem)
{
    //char* path[1025];
    int i;
    if (length == rem-1)
    {
        argv[rem-1] = ' ', argv[rem] = '.', argv[rem+1] = '\0';
        length = rem+1;
    }
    for (i = rem; i <= length; i++)
        path[i-rem] = argv[i];
}

void ls(char* argv, int length)
{
    int i, flagExist = 0, j;

    for (i=0; i<length; i++)
        if (argv[i] == '-') flagExist++;
    findPath(argv, length, 3);
    length = strlen(path);
    if (path[0] == '-')
    {
        if ((path[1] == 'a' && path[2] == 'l') || (path[1] == 'l' && path[2] == 'a') || flagExist == 2)
        {    
            findPath (path, length, (flagExist == 2) ? 6 : 4);
            bothflagsls(path, length);
        }
        else if (path[1] == 'a')
        {
            findPath (path, length, 3);
            lsa (path, length);
        }
        else if (path[1] == 'l')
        {
            findPath (path, length, 3);
            lsl (path, length);
        }
        else 
            printf("ls: invalid option -- \'%c\'\n", path[1]);
        return;
    }
    else
        noflagls (path, length);
}

void noflagls (char* argv, int length)
{
    findPath (argv, length, 3);
    char buf[1025];
    mydir = opendir(path);
    if (mydir == NULL)
        printf("ls: cannot access \'%s\': No such file or directory\n", path);
    else
        while((myfile = readdir(mydir)) != NULL)
        {
            sprintf(buf, "%s/%s", path, myfile->d_name);
            stat(buf, &mystat);
            //printf("%zu",mystat.st_size);
            if (myfile->d_name[0]!='.')
                printf("%s\t\t", myfile->d_name);
        }
    printf("\n");
    closedir(mydir);
}

void lsa (char* argv, int length)
{
    //findPath (argv, length);
    char buf[1025];
    mydir = opendir(path);
    if (mydir == NULL)
        printf("ls: cannot access \'%s\': No such file or directory", path);
    else
        while((myfile = readdir(mydir)) != NULL)
        {
            sprintf(buf, "%s/%s", path, myfile->d_name);
            stat(buf, &mystat);
            //printf("%zu",mystat.st_size);
            //if (myfile->d_name[0]!='.')
            printf("%s\t\t", myfile->d_name);
        }
    printf("\n");
    closedir(mydir);
}

void lsl(char*argv, int length)
{

    //findPath (argv, length);
    //struct group *grp;
    //struct passwd *pwd;
    //grp = getgrgid(gid);
    //pwd = getpwuid(uid);
    char buf[1025];
    mydir = opendir(path);
    if (mydir == NULL)
        printf("ls: cannot access \'%s\': No such file or directory", path);
    else
    {
        int cnt = 0;
        //sprintf(buf, "%s/%s", path, myfile->d_name);
        //stat(buf, &mystat);
        //printf("total %d\n", (int)mystat.st_nlink);
        while((myfile = readdir(mydir)) != NULL)
        {
            sprintf(buf, "%s/%s", path, myfile->d_name);
            stat(buf, &mystat);
            if (myfile->d_name[0]!='.')
            {
            //File Permissions
                printf( (S_ISDIR(mystat.st_mode)) ? "d" : "-");
                printf( (mystat.st_mode & S_IRUSR) ? "r" : "-");
                printf( (mystat.st_mode & S_IWUSR) ? "w" : "-");
                printf( (mystat.st_mode & S_IXUSR) ? "x" : "-");
                printf( (mystat.st_mode & S_IRGRP) ? "r" : "-");
                printf( (mystat.st_mode & S_IWGRP) ? "w" : "-");
                printf( (mystat.st_mode & S_IXGRP) ? "x" : "-");
                printf( (mystat.st_mode & S_IROTH) ? "r" : "-");
                printf( (mystat.st_mode & S_IWOTH) ? "w" : "-");
                printf( (mystat.st_mode & S_IXOTH) ? "x" : "-");
                printf("\t\t%zu",mystat.st_size);

                        //printf("\t\t%s", grp->grp_name);
            //printf("\t\t%s", pwd->pw_name);
                printf("\t\t%s\t", myfile->d_name);
                printf("\n");
                cnt++;
            }
        }
        printf("total %d", cnt);
    }
    closedir(mydir);
}

void bothflagsls(char* argv, int length)
{

    //findPath (argv, length);
    //struct group *grp;
    //struct passwd *pwd;
    //grp = getgrgid(gid);
    //pwd = getpwuid(uid);
    char buf[1025];
    mydir = opendir(path);
    if (mydir == NULL)
        printf("ls: cannot access \'%s\': No such file or directory", path);
    else
    {
        int cnt = 0;
        //sprintf(buf, "%s/%s", path, myfile->d_name);
        //stat(buf, &mystat);
        //printf("total %d\n", (int)mystat.st_nlink);
        while((myfile = readdir(mydir)) != NULL)
        {
            sprintf(buf, "%s/%s", path, myfile->d_name);
            stat(buf, &mystat);

            //File Permissions
            printf( (S_ISDIR(mystat.st_mode)) ? "d" : "-");
            printf( (mystat.st_mode & S_IRUSR) ? "r" : "-");
            printf( (mystat.st_mode & S_IWUSR) ? "w" : "-");
            printf( (mystat.st_mode & S_IXUSR) ? "x" : "-");
            printf( (mystat.st_mode & S_IRGRP) ? "r" : "-");
            printf( (mystat.st_mode & S_IWGRP) ? "w" : "-");
            printf( (mystat.st_mode & S_IXGRP) ? "x" : "-");
            printf( (mystat.st_mode & S_IROTH) ? "r" : "-");
            printf( (mystat.st_mode & S_IWOTH) ? "w" : "-");
            printf( (mystat.st_mode & S_IXOTH) ? "x" : "-");
            printf("\t\t%zu",mystat.st_size);

            //if (myfile->d_name[0]!='.')
            //printf("\t\t%s", grp->grp_name);
           // printf("\t\t%s", pwd->pw_name);
            printf("\t\t%s\t", myfile->d_name);
            printf("\n");
            cnt++;
        }
        printf("total %d", cnt);
    }
    closedir(mydir);

}
