#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Parser the variable

//var ident = value
Statement* parserVar(Parser *p){
    token VarToken = p->cur;
    if(match(p,TYPE_VAR)){
        next(p);
    }
    Ident *ident = malloc(sizeof(Ident));
    if(match(p,TYPE_IDENT)){
        ident->token = p->cur;
        ident->name = p->cur.start;
        next(p);
    }
    else{
        fprintf(stderr,"Error:After var must be ident");
        free(ident);
        return NULL;
    }
    if(match(p,TYPE_ASIGN)){
        next(p);
    }
    else{
        fprintf(stderr,"Error:After ident must be asign");
        free(ident);
        return NULL;
    }
    Expression* value = parserExpression(p);

    Variable* var = malloc(sizeof(Variable));
    
    var->name = ident;
    var->value = value;

    Statement* st_var = malloc(sizeof(Statement));
    st_var->token = VarToken;
    st_var->type = VAR_NODE;
    st_var->node.variable = var;

    return st_var;
}