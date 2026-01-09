#include <stdio.h>  // Standard Input/Output for functions like printf, FILE, fopen, etc.
#include <stdlib.h> // Standard Library for memory allocation (malloc), and other utilities.
#include <ctype.h>  // Character handling functions like isalpha, isdigit, isalnum.
#include <string.h> // String handling functions, particularly memcmp for keyword matching.

// This structure represents the state of our scanner (also known as a lexer).
// The scanner's job is to read the source code character by character and group
// them into a sequence of tokens.
typedef struct {
    const char* start;   // A pointer to the beginning of the token currently being scanned.
    const char* current; // A pointer to the current character being looked at by the scanner.
    int line;            // The current line number in the source file, useful for error reporting.
} Scanner;

// This enumeration defines all the different kinds of tokens our lexer can recognize.
// Each token has a specific type, which helps the parser understand the code's structure.
typedef enum {
    // Literals are tokens that represent a fixed value, like a number or a variable name.
    TOKEN_IDENTIFIER, // A user-defined name, like a variable or function name.
    TOKEN_NUMBER,     // A numeric literal, like 123 or 45.6.
    TOKEN_SYMBOL,     // A symbol that isn't a letter or number (e.g., +, *, {).

    // Keywords are reserved words in the language that have special meaning.
    TOKEN_FUNC,       // The 'func' keyword, used to declare functions.

    // A special token to signify the end of the source file.
    TOKEN_EOF         // "End Of File" token.
} TokenType;


// This structure represents a single token. A token is the smallest meaningful
// unit of code for the parser. It has a type, and it knows where it appeared in
// the source code.
typedef struct {
    TokenType type;      // The type of the token (e.g., TOKEN_NUMBER, TOKEN_IDENTIFIER).
    const char* start;   // A pointer to the beginning of this token's text in the source code.
    int length;          // The number of characters in the token's text.
    int line;            // The line number where this token appears.
} Token;


// -- Scanner Helper Functions --

// Initializes a new scanner.
// This function sets up the scanner to start reading from the beginning of the source code.
void initScanner(Scanner* scanner, const char* source) { // * scanner is the scanner struct and * source is the file being read
    scanner->start = source;   // Point the start of the first token to the beginning of the source.
    scanner->current = source; // The current character also starts at the beginning.
    scanner->line = 1;         // We start at line 1.
}

// Checks if the scanner has reached the end of the source code.
// The end is signified by the null terminator character ('\0').
int isAtEnd(Scanner* scanner) {
    return *scanner->current == '\0';
}

// Consumes the current character and advances the scanner to the next one.
// It returns the character that was just consumed.
char advance(Scanner* scanner) {
    scanner->current++;
    return scanner->current[-1]; // Return the character *before* the increment.
}

// Looks at the current character without consuming it. This is called "lookahead".
// It's useful for deciding what to do next without advancing the scanner.
char peek(Scanner* scanner) {
    return *scanner->current;
}

// Skips over any whitespace characters (spaces, tabs, newlines).
// This is important because whitespace is usually not meaningful to the parser,
// but we need to handle newlines to keep track of the line number.
void skipWhitespace(Scanner* scanner) {
    for (;;) { // An infinite loop that we break out of.
        char c = peek(scanner); // Look at the current character.
        switch (c) {
            case ' ':
            case '\r': // Carriage return
            case '\t': // Tab
                advance(scanner); // If it's whitespace, just consume it and move on.
                break;
            case '\n': // We've encountered a newline character.
                scanner->line++;   // Increment the line counter.
                advance(scanner);  // Consume the newline.
                break;
            default:
                return; // If it's not whitespace, we're done skipping.
        }
    }
}

// -- Token Creation and Scanning --

// A factory function to create a new token.
// It populates a Token struct with the given type and the scanner's current state.
Token makeToken(Scanner* scanner, TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner->start;
    token.length = (int)(scanner->current - scanner->start); // Calculate length from pointers.
    token.line = scanner->line;
    return token;
}

// Determines if a scanned identifier is a keyword or a regular identifier.
static TokenType identifierType(Scanner* scanner) {
    // This uses a switch on the first character for a small optimization.
    // For a large number of keywords, a more advanced structure like a trie or
    // a perfect hash function would be more efficient.
    switch (scanner->start[0]) {
        case 'f':
            // Check for "func". We verify the length (4) and then the rest of the content ("unc").
            if (scanner->current - scanner->start == 4 && memcmp(scanner->start + 1, "unc", 3) == 0) {
                return TOKEN_FUNC;
            }
            break;
    }

    // If it doesn't match any keywords, it's a user-defined identifier.
    return TOKEN_IDENTIFIER;
}

// Scans an identifier or keyword.
// Identifiers can contain letters, numbers, and underscores.
Token identifier(Scanner* scanner) {
    // Keep consuming characters as long as they are alphanumeric or an underscore.
    while (isalnum(peek(scanner)) || peek(scanner) == '_') {
        advance(scanner);
    }
    // Once we've scanned the whole word, check if it's a keyword.
    return makeToken(scanner, identifierType(scanner));
}

// Scans a number literal.
// For simplicity, this lexer only handles integer numbers.
Token number(Scanner* scanner) {
    // Keep consuming characters as long as they are digits.
    while (isdigit(peek(scanner))) {
        advance(scanner);
    }
    // Create a number token.
    return makeToken(scanner, TOKEN_NUMBER);
}

// The main function of the scanner for each turn of the loop.
// It determines the type of the next token and returns it.
Token scanToken(Scanner* scanner) {
    // First, skip any leading whitespace.
    skipWhitespace(scanner);

    // Mark the beginning of the next token.
    scanner->start = scanner->current;

    // Check if we are at the end of the file. If so, return an EOF token.
    if (isAtEnd(scanner)) {
        return makeToken(scanner, TOKEN_EOF);
    }

    // Read the next character to decide what kind of token we have.
    char c = advance(scanner);

    // If the character is a letter or underscore, it's the start of an identifier or keyword.
    if (isalpha(c) || c == '_') return identifier(scanner);
    // If it's a digit, it's the start of a number.
    if (isdigit(c)) return number(scanner);

    // If it's none of the above, we'll just classify it as a generic "symbol".
    // A more complex language would have specific tokens for operators like '+', '-', etc.
    return makeToken(scanner, TOKEN_SYMBOL);
}


// -- File Handling and Main Entry Point --

// A utility function to read an entire file into a dynamically allocated string.
// It also checks if the file exists and can be read.
char* readFile(const char* path) {
    FILE* file = fopen(path, "rb"); // Open the file in binary read mode.
    if (!file) {
        // If the file can't be opened, we can't proceed.
        return NULL;
    }

    // Seek to the end of the file to determine its size.
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file); // Go back to the beginning of the file.

    // Allocate enough memory to hold the entire file content plus a null terminator.
    char* buffer = malloc(size + 1);
    if (!buffer) {
        // If memory allocation fails, we can't read the file.
        fclose(file);
        return NULL;
    }

    // Read the file content into the buffer.
    fread(buffer, 1, size, file);
    buffer[size] = '\0'; // Add the null terminator to make it a valid C string.

    // Clean up by closing the file.
    fclose(file);
    return buffer;
}

// The main entry point of the program.
int main(int argc, char* argv[]) {
    // The program expects one command-line argument: the path to the source file.
    if (argc < 2) {
        printf("Usage: lexer <file>\n");
        return 1; // Exit with an error code.
    }

    // Read the source code from the specified file.
    char* source = readFile(argv[1]);
    if (!source) {
        // If the file could not be read, print an error and exit.
        perror("Could not read file");
        return 1;
    }

    // Create and initialize the scanner.
    Scanner scanner;
    initScanner(&scanner, source);

    // This is the main loop of the lexer. It will keep scanning tokens
    // until it reaches the end of the file.
    for (;;) {
        // Scan one token.
        Token token = scanToken(&scanner);

        // Print the token's line number and type.
        printf("Line %d: ", token.line);
        switch (token.type) {
            case TOKEN_IDENTIFIER: printf("IDENTIFIER   "); break;
            case TOKEN_NUMBER:     printf("NUMBER       "); break;
            case TOKEN_SYMBOL:     printf("SYMBOL       "); break;
            case TOKEN_FUNC:       printf("KEYWORD_FUNC "); break; // Handle the 'func' keyword.
            case TOKEN_EOF:        printf("EOF\n");        break;
        }

        // If we've reached the end of the file, we're done.
        if (token.type == TOKEN_EOF) break;

        // Print the actual text of the token.
        printf("'%.*s'\n", token.length, token.start);
    }

    // Free the memory that was allocated for the source code.
    free(source);
    return 0; // Exit successfully.
}
