#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

StatementBlock* parserBlockStatement(Parser *p){
    if (!match(p, TYPE_LBRACE)) {
        return NULL;
    }
    StatementBlock* block = malloc(sizeof(StatementBlock));
    token Btoken = p->cur;
    block->token = Btoken;
    block->statements = NULL;

    Statement* st;
    for(;p->cur.type != TYPE_EOF && p->cur.type != TYPE_RBRACE ;){
        st = parserStatement(p);
        if(st != NULL){
            block->statements = list_append_value(block->statements,st);
        }
        if(p->cur.type != TYPE_EOF && !match(p, TYPE_RBRACE))
            next(p);
    }
    if(match(p,TYPE_RBRACE)){
        next(p);
    }

    return block;
}