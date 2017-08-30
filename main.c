#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include "spec2.c"
#include "spec4.c"
#include "spec3.c"
#include <sys/wait.h>

char iwd[1024]; //initial working directory
char systemName[65];
struct passwd *user;

/*Currently this function only prints the query. Instead we must process the input:
  i.e. remove extra spaces, determine the flags.
  After that based on the main query of the input string, we must call other functions
  ex. if input was: cd     Documents
  1) make it: cd Documents
  2) call function cd (that we must create ourselves) 
  This can be achieved via some sort of switch case or simple if elseif statements.
*/

void function_caller(char *requestString, int length, char *originalString, int lengthOriginal)
{
  int i=0, pid, flag = 0;
  char iwd2[1025];
  strcpy(iwd2, iwd);
  //printf("%s\n", requestString);
  if(requestString[length - 1] == '&')
    {
      pid = fork();
      requestString[length - 2] = '\0';
      length -= 2;
    }
  else{
    flag = 1;
    pid = fork();
  }
  if(pid == 0){
    if (!strcmp("clear", requestString))
      printf("\033c");
    else if(requestString[0] == 'c' && requestString[1] == 'd')
      cd(requestString, length, iwd2);
    else if (requestString[0] == 'l' && requestString[1] == 's')
      ls(requestString, length);
    else if (!strcmp("pwd", requestString))
      pwd();
    else if (requestString[0] == 'e' && requestString[1] == 'c'&& requestString[2] == 'h' && requestString[3] == 'o')
      echo(requestString, length, originalString, lengthOriginal);
    else
      {
        other_programs(requestString, length);
      }
  }
  else
    {
      if (flag) wait(NULL);
      
      return;
    }
}


void processInput(char *inputString, int length) // This function should parse input string
{
  int i = 0, k=0;
  char processedString[1025];
  for(i = 0; i <= length; i++)
    {
      if(inputString[i] == ' ' && inputString[i + 1] == ' ');
      else if(inputString[i] == ' ' && inputString[i+1] != ' ')
        {processedString[k] = inputString[i]; k++;}
      else if(inputString[i] != ' ')
        {processedString[k] = inputString[i]; k++;}
    }
  if (processedString[k - 2] == ' ') {processedString[k - 2] = '\n'; k--;}
  i = 0;
  if(processedString[0] == ' ')
    {
      k--;
      while(processedString[i] != '\n')
        processedString[i] = processedString[i + 1], i++;
    }
  processedString[k-1] = '\0';
  function_caller(processedString, strlen(processedString), inputString, length);
  return;
}

void print_Prompt() //prints the prompt according to directory 
{
  char restPrompt[1025], pwd[1025], temp[1025];
  int lengthiwd, lengthpwd, k = 1, i, end;
  getcwd(pwd, sizeof(pwd));
  if (!strcmp(iwd, pwd))
    strcpy(restPrompt, "~");
  else {
    if ((lengthpwd = strlen(pwd)) > (lengthiwd = strlen(iwd)))
      {
        for(lengthiwd; lengthiwd < lengthpwd; restPrompt[k] = pwd[lengthiwd], lengthiwd++, k++);
        restPrompt[k] = '\0';
        restPrompt[0] = '~';
      }
    else {
      if (lengthpwd == 1) strcpy(restPrompt, "/");
      else {
        for(k--, lengthpwd - 1; lengthpwd >= 0; lengthpwd--, k++)
          if (pwd[lengthpwd] == '/') break;
          else (temp[k] = pwd[lengthpwd]);
        for(i = 0, end = k; i <= end; i++)
          restPrompt[i] = temp[--k];
        restPrompt[i] = '\0';
      }
    }
  }
  printf("<%s@%s:%s> ", user->pw_name, systemName, restPrompt);
  return;
}

int main()
{
  long long directoryDepth = 0;
  char inputString[1024];
  gethostname(systemName, 64); //systemName has the computer's name
  user = getpwuid(getuid()); //user->pw_name has the username
  getcwd(iwd, sizeof(iwd));
  // For testing purposes uncomment below
  /* print_Prompt(); 
     char path[] = "/home/projit-normal/Documents"; //Change path as required for testing
     chdir(path); 
     print_Prompt(); */
  chdir(iwd);
  while(1){
    print_Prompt();
    int i = 0;
    char temp;
    for(i = 0;; i++)
      {
        scanf("%c", &temp);
        inputString[i] = temp;
        if (temp=='\n') break;
      }
    processInput(inputString, i);
  }
  
  return 0;
}
