#ifndef LEXER_H
#define LEXER_H

typedef enum TokenType{
    TYPE_NUMBER,
    TYPE_VAR,
    TYPE_PLUS,      //+
    TYPE_MINUS,     //-
    TYPE_STAR,      // *
    TYPE_SLASH,     // /
    TYPE_ASIGN,     //=
    TYPE_LPAREN,    //(
    TYPE_RPAREN,    //)
    TYPE_LT,        //<
    TYPE_GT,        //>
    TYPE_COMMA,     //,
    TYPE_COLON,     //:
    TYPE_SEMICOLON, //;
    TYPE_LBRACE,    //{
    TYPE_RBRACE,    //}
    TYPE_LBRACKET,  //[
    TYPE_RBRACKET,  //]
    TYPE_EOF,       //\0
    TYPE_IF,
    TYPE_ELSE,
    TYPE_WHILE,
    TYPE_TRUE,
    TYPE_FALSE,
    TYPE_RETURN,
    TYPE_FUNCTION,
    TYPE_ECHO,
    TYPE_IDENT,
}TokenType;

typedef struct token{
    TokenType type;
    const char *start;
    int leight;
}token;

typedef struct lexer{
    const char *code;
    int pos;
}lexer;

#endif

