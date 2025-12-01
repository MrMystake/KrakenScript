#include "../headers/lexer.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

token MakeToken(TokenType type,const char*start,int leight){
    token t;
    t.type = type;
    t.start = start;
    t.leight = leight;
    return t;
}

lexer* LexerInit(lexer *lex,const char*code){
    lex->code = code;
    lex->pos = 0;
    return lex;
}

token NextToken(lexer *lex){
    const char* s = lex->code;

    while(s[lex->pos] == ' ' || s[lex->pos] ==  '\n' || s[lex->pos] == '\t'){
        lex->pos++;
    }

    char c = s[lex->pos];

    if(isdigit(c)){
        int start = lex->pos;
        while(isdigit(s[lex->pos])) lex->pos++;
        return MakeToken(TYPE_NUMBER,s + start,lex->pos - start);
    }

    if(isalpha(c)){
        int start = lex->pos;
        while(isalnum(s[lex->pos]) || s[lex->pos] == '_') lex->pos++;
        size_t len = lex->pos - start;
        const char* ident = s + start;
    
        struct keyword {
            const char * kw_name;
            TokenType kw_type;
        }const kws[] = {
            {"if",TYPE_IF},
            {"else",TYPE_ELSE},
            {"TRUE",TYPE_TRUE},
            {"FALSE",TYPE_FALSE},
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
        return MakeToken(TYPE_IDENT,ident,len);
    }
    lex->pos++;
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

        default:
            fprintf(stderr,"Uncknow simvol.\n");
            break;
    }
}


int main()
{
    const char *code = "echo 5 *(32-7); MR_mystake_373";
    lexer lex;
    LexerInit(&lex,code);
    token t  = NextToken(&lex);
    while(t.type != TYPE_EOF){
        printf("TOKEN type:%d  value:'%.*s'\n",t.type,t.leight,t.start);
        t = NextToken(&lex);
    }
    return 0;
}