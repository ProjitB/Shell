int convert_Token(char *inputString, char **result)
{
  char *temp  = strtok (inputString, " ");
  int n_spaces = 0, i;

  while (temp) {
    result = realloc (result, sizeof(char*) * (++n_spaces));
    if (result == NULL)
      exit (-1); /* memory allocation failed */
    result[n_spaces - 1] = temp;
    temp = strtok (NULL, " ");
  }
  /* realloc one extra element for the last NULL */
  result = realloc (result, sizeof(char*) * (n_spaces+1));
  result[n_spaces] = 0;

  //result has the strings.
  int status = execvp(result[0], result);
  if(status == -1) printf("Couldn't execute \'%s\'\n", result[0]);
  return n_spaces;
}

void other_programs(char *inputString, int length)
{
  char ** result  = NULL;
  int n_spaces = convert_Token(inputString, result);
  return;
}
