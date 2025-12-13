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