/*
 * v0.0.1 Sunday, November 01 2026
 * For now, the tokenizer should only parse the return value.
 * `int main() { return` (3 + 4) * 2 - 1 `;`} // should output 13
 *
 * What gets built:
 * 1. Tokenizer: for numbers and punctuation (+ - * / ( ) ; )
 * 2. Recursive-descent parser with correct precedence. The grammar is only three levels:
 *      expr    = mul ("+" mul | "-" mul)*
 *      mul     = unary("*" unary | "/" unary)*
 *      unary   = ("-" | "+")? primary
 *      primary = num | "(" expr ")"
*/
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    Stack s;
    initStack(&s);

    if (file == NULL)
    {
        printf("Error: Could not open the file.\n");
        return 1;
    }

    printf("File opened successfully!\n");

    int ch;

    while ((ch = fgetc(file)) != EOF)
    {
        putchar(ch);
    }

    fclose(file);

    return EXIT_SUCCESS;
}
