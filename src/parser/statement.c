#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Parser Statement
Statement* parserStatement(Parser *p){
    if(match(p, TYPE_SEMICOLON) || match(p,TYPE_RBRACE)){
        next(p);
    }
    if(match(p,TYPE_VAR)){
        return parserVar(p);
    }
    else if(match(p,TYPE_RETURN)){
        return parserReturn(p);
    }
    else if(match(p,TYPE_FUNCTION)){
        return parserFunction(p);
    }
    else{
        return parserExprStatement(p);
    }
    fprintf(stderr,"Parser Error: unexpected token  %s",p->cur.start);
    next(p);
    return NULL;
}