void setenviron(char inputString[], int lengthOriginal)
{
  int i = 0, j, flag = 1;
  char *p = strtok (inputString, " ");
  char *array[100];
  
  while (p != NULL)
    {
      array[i++] = p;
      p = strtok (NULL, " ");
    }
  if (i < 2 || i > 3)
    printf("Nopee you are wrong\n"), flag = 0;
  if (flag)
    if (i == 2)
      setenv(array[1], "", 1);
    else setenv(array[1], array[2], 1);
  return;
}

void unsetenviron(char inputString[], int lengthOriginal)
{
  int i = 0, j, flag = 1;
  char *p = strtok (inputString, " ");
  char *array[100];
  while (p != NULL)
    {
      array[i++] = p;
      p = strtok (NULL, " ");
    }
  if (i == 2) unsetenv(array[1]);
  else printf("Nopee you are wrong\n");
  return;
}
