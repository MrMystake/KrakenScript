#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Parser return statement

//return value
Statement* parserReturn(Parser *p){
    ReturnStatement* ret = malloc(sizeof(ReturnStatement));
    token ReturnToken = p->cur;
    if(match(p,TYPE_RETURN)){
        next(p);
    }
    Expression* value = parserExpression(p);
    ret->token = ReturnToken;
    ret->return_value = value;

    Statement* st_return = malloc(sizeof(Statement));
    st_return->token = ReturnToken;
    st_return->type = RETURN_NODE;
    st_return->node.st_return = ret;

    return st_return;
}