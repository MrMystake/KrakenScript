#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void next(Parser *p){
    p->cur = p->next;
    p->next = NextToken(p->lex);
}


int match(Parser *p, TokenType type){
    if (p->cur.type == type) {
        return 1;
    }
    return 0;
}

bool StringBool(Parser *p){
    if (strcmp(p->cur.start,"true") == 0) return true;
    if (strcmp(p->cur.start,"false") == 0) return false;
    return false;
}

void ParserInit(Parser *p,lexer *lex){
    p->lex = lex;
    p->cur = NextToken(lex);
    p->next = NextToken(lex);
}

Expression* parserExpression(Parser *p){
    return parserSum(p);
}

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
    else if(match(p,TYPE_STRING)){
        Expression *node = malloc(sizeof(Expression));
        node->token = p->cur;
        node->token_literal = p->cur.start;
        node->type = STRING_NODE;
        node->node.string.token = p->cur;
        node->node.string.value = p->cur.start;

        next(p);
        return node;
    }
    else if(match(p,TYPE_TRUE) || match(p,TYPE_FALSE)){
        Expression *node = malloc(sizeof(Expression));
        node->token = p->cur;
        node->token_literal = p->cur.start;
        node->type = BOOLEAN_NODE;
        node->node.boolean.token = p->cur;
        node->node.boolean.value = StringBool(p);

        next(p);
        return node;
    }
    else if(match(p,TYPE_LPAREN)){
        next(p);
        Expression *node = parserExpression(p);
        match(p,TYPE_RPAREN);

        next(p);
        return node;
    }
}


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