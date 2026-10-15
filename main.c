/*
 ***************************************************************************
 * Version 0.1 of the basic compiler
 * Key words:
 *    set - used to declare and assign values to variables
 *    print - used to ouput variables or values
 * Identifier rules:
 * An Identifier is the name you assign to a variable.
 * For MiniLang, the rules are:
 *    Starting character: a-z, A-Z, or _
 *    Subsequent characters: a-z, A-Z, 0-9, or _
 *    Reserved check: cannot match any language keyword
 *    RegexPattern: [a-zA-Z_][a-zA-Z0-9_]*
 *    Valid examples: x, score, my_var, _temp2
 *    Invalid examples: 2fast, set
 * Expression Rules:
 * a valid unit of code that evaluates a value is an expression.
 * In MiniLang, an expression can take one of three forms.
 *    1. Literal Numbers: A raw integer value
 *    2. Identifier: A reference to a variable
 *    3. Binary Operation: Two terms separated by a mathematical operator
 ***************************************************************************
*/
#include <stdio.h>
#include "stack.h"

#define MAX 100

int main(int argc, char *argv[])
{
  Node *stack = NULL;

  // Check if the user has provided a file
  if (argc < 2)
  {
    printf("Error: Missing filename.\n");
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  // Open the file the user passed
  // Open using "r" for read mode
  FILE *file_ptr = fopen(argv[1], "r");

  // Check if the file exists
  if (file_ptr == NULL)
  {
    printf("Error: Could not open file '%s'. It may not exist.\n", argv[1]);
    return 1;
  }

  int ch; // The next characters, used int to properly catch EOF
  int idx = 0;
  char buffer[MAX];
  char text[2];

  printf("--- Displaying contents of %s ---\n", argv[1]);

  // looping through the file and outputting it.
  while ((ch = fgetc(file_ptr)) != EOF)
  {
    if (ch == ' ' || ch == '\n' || ch == '\t')
    {
      if (idx > 0)
      {
        buffer[idx] = '\0';
        idx = 0;
      }
      push(&stack, buffer);
      text[0] = ch;
      text[1] = '\0';
      push(&stack, text);
    }
    else
    {
      if (idx < MAX - 1)
      {
        buffer[idx] = (char)ch;
        idx++;
      }
      else
      {
        printf("\nWarning: Word exceeded buffer length limit. Splitting word.\n");
        buffer[idx] = '\0';
        push(&stack, buffer);
        idx = 0;
      }
    }
  }

  if (idx > 0)
  {
    buffer[idx] = '\0';
    push(&stack, buffer);
  }

  printf("\n--- End of File ---\n");

  // Closing the file and clean up resources
  fclose(file_ptr);

  return 0; // success
}
