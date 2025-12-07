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

#endif