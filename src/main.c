// TODO(#5): Test and upgrade

// FIXME: Refactor the code
// FIXME: Replace constant constraints (like maximum SymbolTable size)
// FIXME: Include only needed functions in header files, "optimize" file structure
// BUG: Parsing the return statements (just number not ID's)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/interpreter.h"
#include "../include/utils/load_code.h"

// MAIN
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Please provide filename for WLan interpreter\n");
        exit(EXIT_FAILURE);
    }
    const char *filename = argv[1];
    char *source_code = get_source_code(filename);
    if (source_code == NULL)
    {
        fprintf(stderr, "Couldnt load the file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    int num_tokens;

    Token *tokens = lexer(source_code, &num_tokens);

    printf("\nLEXER \n");
    print_tokens(tokens, num_tokens);
    printf("\nParser \n");
    ASTNode *ASTree = parse_program(&tokens);
    print_ASTree(ASTree, 0);

    printf("\nInterpreter \n");
    ScopeStack memoryStack;
    init_ScopeStack(&memoryStack, 500);
    push_scope(&memoryStack, 2000);
    evaluate(ASTree, &memoryStack);

    free(source_code);
    free(tokens);
    // free_ASTree(ASTree);
    return 0;
}
