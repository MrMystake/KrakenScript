#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parses a addition and subtraction
Expression* parserSum(Parser *p){
    Expression *left = parserTerm(p);

    while(match(p,TYPE_PLUS) || match(p,TYPE_MINUS)){
        Expression* parent = malloc(sizeof(Expression));

        parent->token = p->cur;
        parent->token_literal = p->cur.start;
        parent->type = BINARY_NODE;
        parent->node.binary.token = p->cur;
        parent->node.binary.operator = p->cur.type;
        next(p);

        Expression* right = parserTerm(p);
        parent->node.binary.left = left;
        parent->node.binary.right = right;
        left = parent;
    }
    return left;
}