#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//x + x ;name()
Statement* parserExprStatement(Parser *p){
    Expression* expression = parserExpression(p);
    Statement *st = malloc(sizeof(Statement));
    ExpressionStatement* ExprState = malloc(sizeof(ExpressionStatement));
    ExprState->token = p->cur;
    ExprState->expression = expression;

    st->token = p->cur;
    st->type = EXPRESSION_STATEMENT_NODE;
    st->node.st_expr = ExprState;

    return st;
}