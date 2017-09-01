int convert_Token(char *inputString, char **result)
{
  char *  p    = strtok (inputString, " ");
  int n_spaces = 0, i;

  /* split string and append tokens to 'result' */

  while (p) {
    result = realloc (result, sizeof(char*) * ++n_spaces);

    if (result == NULL)
      exit (-1); /* memory allocation failed */

    result[n_spaces-1] = p;

    p = strtok (NULL, " ");
  }

  /* realloc one extra element for the last NULL */

  result = realloc (result, sizeof(char*) * (n_spaces+1));
  result[n_spaces] = 0;

  //result has the strings.
    
  execvp(result[0], result);
  
  return n_spaces;
}

void other_programs(char *inputString, int length)
{
  char ** result  = NULL;
  int n_spaces = convert_Token(inputString, result);
  return;
}
