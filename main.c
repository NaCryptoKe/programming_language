/*
 * MiniLang lexer. Keywords: set, print.
 * Identifiers match [a-zA-Z_][a-zA-Z0-9_]*.
 * Expressions are numeric literals or tokens containing an arithmetic
 * operator.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define MAX 100

static const char *classify(const char *token)
{
  if (strcmp(token, "set") == 0 || strcmp(token, "print") == 0)
    return "keyword";

  if (isdigit((unsigned char)token[0]) || strchr(token, '+') != NULL ||
      strchr(token, '-') != NULL || strchr(token, '*') != NULL ||
      strchr(token, '/') != NULL)
    return "expression";

  if (isalpha((unsigned char)token[0]) || token[0] == '_')
    return "identifier";

  return "expression";
}

int main(int argc, char *argv[])
{
  Queue queue = {NULL, NULL};
  char buffer[MAX];
  size_t idx = 0;
  int ch;

  if (argc < 2)
  {
    fprintf(stderr, "Error: Missing filename.\nUsage: %s <filename>\n", argv[0]);
    return 1;
  }

  FILE *file_ptr = fopen(argv[1], "r");
  if (file_ptr == NULL)
  {
    fprintf(stderr, "Error: Could not open file '%s'.\n", argv[1]);
    return 1;
  }

  /* Step 1: split the input into whitespace-delimited tokens. */
  while ((ch = fgetc(file_ptr)) != EOF)
  {
    if (isspace((unsigned char)ch))
    {
      if (idx > 0)
      {
        buffer[idx] = '\0';
        enqueue(&queue, buffer);
        idx = 0;
      }
    }
    else if (idx < sizeof(buffer) - 1)
    {
      buffer[idx++] = (char)ch;
    }
    else
    {
      buffer[idx] = '\0';
      enqueue(&queue, buffer);
      idx = 0;
      buffer[idx++] = (char)ch;
    }
  }
  if (idx > 0)
  {
    buffer[idx] = '\0';
    enqueue(&queue, buffer);
  }
  fclose(file_ptr);

  /* Step 2: dequeue every token in input order and report its kind. */
  char *token;
  while ((token = dequeue(&queue)) != NULL)
  {
    printf("%s: %s\n", classify(token), token);
    free(token);
  }

  freeQueue(&queue);
  return 0;
}
