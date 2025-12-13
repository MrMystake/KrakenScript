#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parses the smallest unit of an expression (a "factor").
// A factor can be a number, string, boolean, identifier, or
// an expression inside parentheses. This function reads the
// current token and returns the corresponding expression node.
Expression* parserFactor(Parser *p){
    Expression *node = malloc(sizeof(Expression));
    if(match(p,TYPE_NUMBER)){
        node->token = p->cur;
        node->token_literal = p->cur.start;
        node->type = NUMBER_NODE;
        node->node.number.token = p->cur;
        node->node.number.value = atoi(p->cur.start);

        next(p);
        return node;
    }
    else if(match(p,TYPE_STRING)){
        node->token = p->cur;
        node->token_literal = p->cur.start;
        node->type = STRING_NODE;
        node->node.string.token = p->cur;
        node->node.string.value = p->cur.start;

        next(p);
        return node;
    }
    else if(match(p,TYPE_TRUE) || match(p,TYPE_FALSE)){
        node->token = p->cur;
        node->token_literal = p->cur.start;
        node->type = BOOLEAN_NODE;
        node->node.boolean.token = p->cur;
        node->node.boolean.value = StringBool(p);

        next(p);
        return node;
    }
    else if(match(p,TYPE_IDENT)){
        node->token = p->cur;
        node->token_literal = p->cur.start;
        node->type = VAR_IDENT;
        node->node.varName.token = p->cur;
        node->node.varName.name = p->cur.start;

        next(p);
        return node;
    }
    else if(match(p,TYPE_LPAREN)){
        next(p);
        node = parserExpression(p);
        match(p,TYPE_RPAREN);

        next(p);
        return node;
    }
    return node;
}