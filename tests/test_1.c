#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include "../headers/Interpreter.h"
#include <stdio.h>

int main()
{

    const char* code = "100 / (5+5 *2) + 10 * 2 + 1000/10";
    lexer lexer;
    LexerInit(&lexer,code);

    Parser parser;
    ParserInit(&parser,&lexer);

    Expression *ast = parserExpression(&parser);

    int result = evalExpression(ast);
    printf("Результат:%d",result);
    return 0;
}


