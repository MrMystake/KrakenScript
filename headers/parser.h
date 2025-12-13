#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "token.h"
#include "ast.h"


typedef struct Parser{
    lexer *lex;
    token cur;
    token next;
}Parser;

typedef enum Precedence{
    LOWEST,
    EQUALS,         // =,==
    SUM,            //+,-
    PRODUCT,        //*,/
    LESSGREATER,    //< >
    PREFIX,         //-x !x
    CALL,           // func()

}Precedence;
//utils.c
void next(Parser *p);
bool StringBool(Parser *p);
int match(Parser *p, TokenType type);
void ParserInit(Parser *p,lexer *lex);

//factor.c
Expression* parserFactor(Parser *p);

//term.c
Expression* parserTerm(Parser *p);

//sum.c
Expression* parserSum(Parser *p);

//expression.c
Expression* parserExpression(Parser *p);

//var.c
Statement* parserVar(Parser *p);

//return.c
Statement* parserReturn(Parser *p);

//expr_statement.c
Statement* parserExprStatement(Parser *p);

//block_statement.c
StatementBlock* parserBlockStatement(Parser *p);

//functoin.c
Statement* parserFunction(Parser *p);

//function_parameters.c
List* parserFuncParameters(Parser *p);

//call_function.c
Statement* parserCallFunc(Parser *p);

//statement.c
Statement* parserStatement(Parser *p)

//program.c
Program* parserProgram(Parser *p);

//free.c
void FreeExpression(Expression *expr);
void FreeStatement(Statement *st);
void FreeList(List *list);
void FreeBlockStatement(List *list);

#endif