#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>


int remove_last(char *inputString, int length)
{
  int i;
  for(i = length - 1; i >= 0; i--)
      if (inputString[i] == '/') break;
  inputString[i] = '\0';
  return i;
}

int add_section(char *inputString, char*section, int lengthInput, int lengthSection)
{
  int i, j;
  inputString[lengthInput] = '/';
  for(i = lengthInput + 1, j = 0; j < lengthSection; i++, j++)
      inputString[i] = section[j];
  inputString[i] = '\0';
  return i;
}

int changing(char *path, char *pwd, int pathlen, int casetype)
{
  char buffer[1025];
  int i, bufi = 0, flag = 0;
  for(i = (casetype == 1)? 1: 0, bufi = 0; i < pathlen; i++, bufi++)
      {
        if (path[i] == '/')
          {
            buffer[bufi] = '\0';
            if(!strcmp(buffer, "../"))
              {
                remove_last(pwd, strlen(pwd));
                flag = chdir(pwd);  
              }
            else
              {
                add_section(pwd, buffer, strlen(pwd), strlen(buffer));
                flag = chdir(pwd);  
              }
            bufi = -1;
            if(flag == -1) break;
          }
        else buffer[bufi] = path[i];
      }
  return flag;
}

void cd(char *inputString, int length, char* iwd)
{
  char path[1025], pwd[1025], pwdSaved[1025];
  getcwd(pwdSaved, sizeof(pwdSaved));
  getcwd(pwd, sizeof(pwd));
  int i;
  for(i = 3; i <= length; i++)
      path[i - 3] = inputString[i];
  int pathlen = strlen(path), flag, bufi;
  if (path[pathlen -1] != '/') path[pathlen] = '/', path[pathlen + 1] = '\0', pathlen++;
  if(path[0] != '/' && path[0] != '~')
    {
      if (path[0] == '.' && path[1] == '/')
        flag = changing(path, pwd, pathlen, 1);
      else
        flag = changing(path, pwd, pathlen, 0);
    }
  else if(path[0] == '~')
    flag = changing(path, iwd, pathlen, 1);
  else if(path[0] == '/')
    flag = chdir(path);
  if (flag == -1) printf("Couldn't change directory!!\n"), chdir(pwdSaved);
 return;
}

