#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "lexer.c"// Assuming your lexer code is in lexer.h and lexer.c
#include "parser.c"
#include "parser.h"

Token *tokens;

int main() {
    setlocale(LC_CTYPE, "");

    FILE *file = fopen("source_code.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Determine the length of the file
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file contents
    wchar_t *input = malloc((length + 1) * sizeof(wchar_t));
    if (!input) {
        wprintf(L"Failed to allocate memory for file content\n");
        fclose(file);
        return 1;
    }

    // Read the file into the allocated array
    int i = 0;
    wint_t wc;
    while ((wc = fgetwc(file)) != WEOF) {
        input[i++] = wc;
    }
    input[i] = L'\0';

    fclose(file);

    // Tokenize the input
    tokens = tokenize(input);


    
    parseProgram();

    // Free allocated memory for tokens and input (don't forget to free memory after usage)
    freeSymbolTable();
    free(tokens);
    free(input);

    return 0;
}
