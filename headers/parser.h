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

void next(Parser *p);
bool StringBool(Parser *p);
int match(Parser *p, TokenType type);
void ParserInit(Parser *p,lexer *lex);

Expression* parserFactor(Parser *p);
Expression* parserTerm(Parser *p);
Expression* parserExpression(Parser *p);
Expression* parserSum(Parser *p);

Statement* parserVar(Parser *p);
Statement* parserReturn(Parser *p);
Statement* parserStatement(Parser *p);
Statement* parserExprStatement(Parser *p);
StatementBlock* parserBlockStatement(Parser *p);
Statement* parserFunction(Parser *p);
List* parserFuncParameters(Parser *p);
Statement* parserCallFunc(Parser *p);


Program* parserProgram(Parser *p);
#endif