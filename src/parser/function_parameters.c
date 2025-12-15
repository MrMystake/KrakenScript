#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Parser parameters  for function declaration and arguments for Call function

List* parserFuncParameters(Parser *p){
    List* params = NULL;
    if(match(p,TYPE_RPAREN)){
        next(p);
        return params;
    }
    if(!match(p,TYPE_IDENT)){
        fprintf(stderr,"Error: expected parameter name\n");
        return NULL;
    }
    params = list_append_value(params, (void*)p->cur.start);
    next(p);
    while(match(p,TYPE_COMMA)){
        next(p);
        if(!match(p,TYPE_IDENT)){
            fprintf(stderr,"Error: expected identifier after ','\n");
            return NULL;
        }
        params = list_append_value(params, (void*)p->cur.start);
        next(p);
    }
    if(!match(p,TYPE_RPAREN)){
        fprintf(stderr, "Error: expected ')'\n");
        return NULL;
    }
    return params;
}