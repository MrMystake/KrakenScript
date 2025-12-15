#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parses the smallest unit of an expression (a "factor").
Expression* parserFactor(Parser *p){
    if(match(p,TYPE_NUMBER)){
        Expression *node = malloc(sizeof(Expression));
        node->token = p->cur;
        node->token_literal = p->cur.start;
        node->type = NUMBER_NODE;
        node->node.number.token = p->cur;
        node->node.number.value = atoi(p->cur.start);

        next(p);
        return node;
    }
    if(match(p,TYPE_STRING)){
        Expression *node = malloc(sizeof(Expression));
        node->token = p->cur;
        node->token_literal = p->cur.start;
        node->type = STRING_NODE;
        node->node.string.token = p->cur;
        node->node.string.value = p->cur.start;

        next(p);
        return node;
    }
    if(match(p,TYPE_TRUE) || match(p,TYPE_FALSE)){
        Expression *node = malloc(sizeof(Expression));
        node->token = p->cur;
        node->token_literal = p->cur.start;
        node->type = BOOLEAN_NODE;
        node->node.boolean.token = p->cur;
        node->node.boolean.value = StringBool(p);

        next(p);
        return node;
    }
    if(match(p,TYPE_IDENT)){
        Expression *node = malloc(sizeof(Expression));
        node->token = p->cur;
        node->token_literal = p->cur.start;
        node->type = VAR_IDENT;
        node->node.ident.token = p->cur;
        node->node.ident.name = p->cur.start;

        next(p);
        return node;
    }
    else if(match(p,TYPE_LPAREN)){
        Expression *node = malloc(sizeof(Expression));
        next(p);
        node = parserExpression(p);
        match(p,TYPE_RPAREN);

        next(p);
        return node;
    }
    next(p);
    return NULL;
}