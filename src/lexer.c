//-------------------------
//          lexer
//-------------------------

#include "../headers/lexer.h"
#include "../headers/token.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//create Lexer
lexer LexerInit(lexer *lex,const char*code){
    lex->code = code;
    lex->pos = 0;
    return *lex;
}

//goes through the entire code and creates tokens
token NextToken(lexer *lex){
    const char* s = lex->code;

    while(s[lex->pos] == ' ' || s[lex->pos] ==  '\n' || s[lex->pos] == '\t'){
        lex->pos++;
    }

    char c = s[lex->pos];

    //number token
    if(isdigit(c)){
        int start = lex->pos;
        while(isdigit(s[lex->pos])) lex->pos++;
        return MakeToken(TYPE_NUMBER,s + start,lex->pos - start);
    }

    //words token
    if(isalpha(c)){
        int start = lex->pos;
        while(isalnum(s[lex->pos]) || s[lex->pos] == '_') lex->pos++;
        size_t len = lex->pos - start;
        const char* ident = s + start;
    
        //reserved words
        struct keyword {
            const char * kw_name;
            TokenType kw_type;
        }const kws[] = {
            {"if",TYPE_IF},
            {"else",TYPE_ELSE},
            {"true",TYPE_TRUE},
            {"false",TYPE_FALSE},
            {"while",TYPE_WHILE},
            {"return",TYPE_RETURN},
            {"func",TYPE_FUNCTION},
            {"var",TYPE_VAR},
            {"echo",TYPE_ECHO},
        };

        const  size_t kws_count = sizeof kws / sizeof kws[0];

        for(size_t i = 0; i < kws_count; i++){
            if(strncmp(ident,kws[i].kw_name,len) == 0 &&  strlen(kws[i].kw_name) == len)
                return MakeToken(kws[i].kw_type,ident,len);
        }
        return MakeToken(TYPE_STRING,ident,len);
    }
    lex->pos++;
    
    //single tokens
    switch(c){
        case '+':return MakeToken(TYPE_PLUS,"+",1);
        case '-':return MakeToken(TYPE_MINUS,"-",1);
        case '*':return MakeToken(TYPE_STAR,"*",1);
        case '/':return MakeToken(TYPE_SLASH,"/",1);
        case '=':return MakeToken(TYPE_ASIGN,"=",1); 
        case '(':return MakeToken(TYPE_LPAREN,"(",1);
        case ')':return MakeToken(TYPE_RPAREN,")",1);
        case '{':return MakeToken(TYPE_LBRACE,"{",1);
        case '}':return MakeToken(TYPE_RBRACE,"}",1);
        case '[':return MakeToken(TYPE_LBRACKET,"[",1);
        case ']':return MakeToken(TYPE_RBRACKET,"]",1);
        case ',':return MakeToken(TYPE_COMMA,",",1);
        case ':':return MakeToken(TYPE_COLON,":",1);
        case ';':return MakeToken(TYPE_SEMICOLON,";",1);
        case '\0':return MakeToken(TYPE_EOF,"\0",1);
        case '\n':return MakeToken(TYPE_EOL,"\n",1);
    }
}