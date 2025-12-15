#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//additional functions

//move the token forward
void next(Parser *p){
    p->cur = p->next;
    p->next = NextToken(p->lex);
}

//compare p with TYPE_TOKEN
int match(Parser *p, TokenType type){
    if (p->cur.type == type) {
        return 1;
    }
    return 0;
}

//help for compare p with string "true" or "false"
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