//----------------------------
//          Token
//----------------------------

#include "../headers/lexer.h"
#include "../headers/token.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//MakeToken
token MakeToken(TokenType type,const char*start,int leight){
    token t;
    t.type = type;
    t.start = start;
    t.leight = leight;
    return t;
}