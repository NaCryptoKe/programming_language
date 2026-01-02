#include <stdio.h>

typedef struct {
    const char* start;
    const char* current;
    int line;
} Scanner;

int main(int argc, char* argv[]) {
    FILE *fptr = fopen ("hello.nulo", "r");

    if (fptr == NULL) {
        perror("File open failed");
        return 1;
    }
    
    int ch;

    while((ch = fgetc(fptr)) != EOF){
        if(ch == ' ' || ch == '\n' || ch == '\t' || ch == '(' || ch == '{' || ch == '}' || ch == ')' || ch == ';'){
            printf("\n");
            printf("%c", ch);
        } else {
            printf("%c", ch);
        }
    }
    
    fclose(fptr);

    return 0;
}
