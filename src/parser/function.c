#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Parser function declaration

// func name(parametrs){body}
Statement* parserFunction(Parser *p){
    FunctionStatement* func = malloc(sizeof(FunctionStatement));
    token Ftoken = p->cur;

    if(match(p,TYPE_FUNCTION)){
        func->token = Ftoken;
        next(p);
    }

    if(match(p,TYPE_IDENT)){
        func->name = p->cur.start;
        next(p);
    }
    else{
        fprintf(stderr,"Error: expected function name\n");
        free(func);
        return NULL;
    }

    if(match(p,TYPE_LPAREN)){
        next(p);
        func->parameters = parserFuncParameters(p);
    }
    else{
        fprintf(stderr,"Error:Expected (\n");
        free(func);
        return NULL;
    }

    if(!match(p,TYPE_RPAREN)){
        fprintf(stderr,"Error:Expected )\n");
        free(func);
        return NULL;  
    }
    next(p);

    if(!match(p,TYPE_LBRACE)){
    fprintf(stderr, "Parser Error: Expected {\n");
    free(func);
    return NULL;
    }
    next(p);
    func->body = parserBlockStatement(p);


    Statement *st = malloc(sizeof(Statement));
    st->token = Ftoken;
    st->type = FUNCTION_NODE;
    st->node.func = func;

    return st;
}