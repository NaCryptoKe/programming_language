#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// A struct for scanning the file contents char by char
typedef struct {
    const char* start;
    const char* current;
    int line;
} Scanner;

// The type a token can be
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_SYMBOL,
    TOKEN_EOF
} TokenType;

// A struct for the token it self
typedef struct {
    TokenType type;
    const char* start;
    int length;
    int line;
} Token;

// Scanner Helpers
// Initialization of the scanner before use
void initScanner(Scanner* scanner, const char* source) { // * scanner is the scanner struct and * source is the file being read
    scanner->start = source; // setting the start to the sources first char
    scanner->current = source; // setting the current to the sources first char
    scanner->line = 1; // setting the line count to 1
}

// A simple function to tell if we have reached the end of the file or not
int isAtEnd(Scanner* scanner) {
    return *scanner->current == '\0';
}

// a function to go to the next char after checking the current one
char advance(Scanner* scanner) {
    scanner->current++;
    return scanner->current[-1];
}

// checks what the current char has in it
char peek(Scanner* scanner) {
    return *scanner->current;
}

// checks for spaces (' '), escape sequence ('\r') and a tab ('\t'). If it encounters a new line ('\n') it adds one to the line to indicate we have gone to a new line
void skipWhitespace(Scanner* scanner) {
    for (;;) {
        char c = peek(scanner);
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance(scanner); // calling the advance scanner method, to add 1 to the current value
                break;
            case '\n': // We've encountered a new line
                scanner->line++;
                advance(scanner);
                break;
            default:
                return;
        }
    }
}

// a token function the creates a token, takes the scanner and token type
Token makeToken(Scanner* scanner, TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner->start;
    token.length = (int)(scanner->current - scanner->start);
    token.line = scanner->line;
    return token;
}

// Identifies what token type the current token is
Token identifier(Scanner* scanner) {
    while (isalnum(peek(scanner)) || peek(scanner) == '_') {
        advance(scanner);
    }
    return makeToken(scanner, TOKEN_IDENTIFIER);
}

// checks if token is a number
Token number(Scanner* scanner) {
    while (isdigit(peek(scanner))) {
        advance(scanner);
    }
    return makeToken(scanner, TOKEN_NUMBER);
}

// 
Token scanToken(Scanner* scanner) {
    skipWhitespace(scanner);

    scanner->start = scanner->current; // updates the start to the current and will now start a new token scanning

    if (isAtEnd(scanner)) {
        return makeToken(scanner, TOKEN_EOF); // a token for End Of File
    }

    char c = advance(scanner);

    if (isalpha(c) || c == '_') return identifier(scanner);
    if (isdigit(c)) return number(scanner);

    // Everything else = single-character symbol (v1 simplicity)
    return makeToken(scanner, TOKEN_SYMBOL);
}

// A simple function to read a file, also checks if the file exists in the first place.
char* readFile(const char* path) {
    FILE* file = fopen(path, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* buffer = malloc(size + 1);
    if (!buffer) return NULL;

    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    fclose(file);
    return buffer;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: lexer <file>\n");
        return 1;
    }

    char* source = readFile(argv[1]);
    // if the file doesn't exist
    if (!source) {
        perror("Could not read file");
        return 1;
    }

    Scanner scanner;
    initScanner(&scanner, source);

    // A simple loop to go through the source file till the end of the file
    for (;;) {
        Token token = scanToken(&scanner);

        printf("Line %d: ", token.line);
        switch (token.type) {
            case TOKEN_IDENTIFIER: printf("IDENTIFIER "); break;
            case TOKEN_NUMBER:     printf("NUMBER "); break;
            case TOKEN_SYMBOL:     printf("SYMBOL "); break;
            case TOKEN_EOF:        printf("EOF\n"); break;
        }

        if (token.type == TOKEN_EOF) break;

        printf("'%.*s'\n", token.length, token.start);
    }

    free(source);
    return 0;
}
