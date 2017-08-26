#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include<string.h>

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
void processInput(char *inputString) // This function should parse input string
{
  int i = 0;
  while(inputString[i] != '\n')
    printf("%c", inputString[i++]);
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

  while(1){
    print_Prompt();
    int i = 0;
    char temp;
    for(i = 0;; i++)
      {
        scanf("%c", &temp);
        if (temp=='\n') {inputString[i] = '\n'; break;}
        else inputString[i] = temp;
      }
    processInput(inputString);
  }
  
  return 0;
}
