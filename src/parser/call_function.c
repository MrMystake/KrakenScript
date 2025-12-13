#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//name(num_1,num_2)
Statement* parserCallFunc(Parser *p){
    token CFtoken = p->cur;
    CallFunctionStatement* call_func = malloc(sizeof(CallFunctionStatement));
    Statement *st = malloc(sizeof(Statement));

    if(match(p,TYPE_IDENT)){
        call_func->token = CFtoken;
        call_func->func_name = p->cur.start;
        next(p);
    }
    else{
        fprintf(stderr,"Error: expected parameter name\n");
        return NULL;
    }

    if(match(p,TYPE_LPAREN)){
        next(p);
        call_func->arguments = parserFuncParameters(p);
    }
    else{
        fprintf(stderr,"Error:Expected (\n");
        return NULL;
    }
    st->token = CFtoken;
    st->type = CALL_FUNCTION_NODE;
    st->node.call_func = call_func;
    
    return st;
}