//--------------------------
//          Parser
//--------------------------

#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//additional functions
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

//create Parser
void ParserInit(Parser *p,lexer *lex){
    p->lex = lex;
    p->cur = NextToken(lex);
    p->next = NextToken(lex);
}


// Parses a full expression.
// This is the top-level expression parser that handles operator
// precedence by calling lower-level parsers (sum, term, factor).
// It returns the final expression tree representing the entire expression.
Expression* parserExpression(Parser *p){
    return parserSum(p);
}


// Parses the smallest unit of an expression (a "factor").
// A factor can be a number, string, boolean, identifier, or
// an expression inside parentheses. This function reads the
// current token and returns the corresponding expression node.
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


//// Parses a sum-level expression.
// This handles addition and subtraction. It first parses a term,
// then checks for + or - operators and builds a binary expression
// tree while these operators are present.
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