#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct lexer{
    const char *code;
    int pos;
}lexer;

lexer LexerInit(lexer *lex,const char*code);
token NextToken(lexer *lex);

#endif

