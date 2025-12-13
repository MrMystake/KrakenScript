#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parses a term in an expression.
// A term usually handles multiplication, division, and modulo.
// It takes the left factor, checks for * / % operators,
// and builds a binary expression tree while such operators appear.
Expression* parserTerm(Parser *p){
    Expression *left = parserFactor(p);

    while(match(p,TYPE_STAR) || match(p,TYPE_SLASH)){
        Expression *parent = malloc(sizeof(Expression));

        parent->token = p->cur;
        parent->token_literal = p->cur.start;
        parent->type = BINARY_NODE;
        parent->node.binary.token = p->cur;
        parent->node.binary.operator = p->cur.type;
        next(p);

        Expression *right = parserFactor(p);
        parent->node.binary.left = left;
        parent->node.binary.right = right;
        left = parent;
    }
    return left;
}