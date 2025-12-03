#ifndef AST_H
#define AST_H


#include "lexer.h"
#include "../utils/list.h"

//-------------------------------------
//Expresion
//-------------------------------------

typedef enum ExpressionNodeType{
    EXPRESSION_NODE,
    EXPRESSION_STATEMENT_NODE,
    EXPRESSION_NUMBER_NODE,
    EXPRESSION_BOOLEAN_NODE,
    EXPRESSION_STRING_NODE,
}ExpressionNodeType;

typedef struct Expression{
    token *token;
    const char * token_literal;
    void*node;
}Expression;

typedef struct ExpressionStatement{
    token *token;
    Expression *expression;
}ExpressionStatement;

typedef struct {
    token *token;
    int value;
}NumberLiteral;

typedef struct{
    token *token;
    bool value;
}BooleanLiteral;

typedef struct{
    token *token;
    const char* value;
}StringLiteral;

typedef struct{
    token *token;
    const char *operator;
    Expression *left;
    Expression *right;
}BinaryExpr;

typedef struct{
    token *token;
    Expression *conditional;
    StatementBlock *if_block;
    StatementBlock *else_block;
}ExpressionIf;

//-------------------------------------
//Statement
//-------------------------------------

typedef enum StatementNodeType{
    PROGRAM_NODE,
    STATEMENT_NODE,
    STATEMENT_BLOCK_NODE,
    VAR_STATEMENT_NODE,
    RETURN_STATEMENT_NODE,
}StatementNodeType;

typedef struct Statement{
    token *token;
    const char* token_literal;
    void *node;
}Statement;

typedef struct StatementBlock{
    token *token;
    List *statements;
}StatementBlock;

typedef struct{
    token *token;
    Expression *return_value;
}ReturnStatement;

typedef struct{
    token *token;
    const char *name;
}VarName;

typedef struct{
    token *token;
    VarName *name;
    Expression *value;
}Variable;

typedef struct{
    token *token;
    const char *name;
    List *parameters;
    StatementBlock *body;
}FunctionStatement;

typedef struct{
    token *token;
    Expression *func;
    List *arguments;
}CallFunctionStatement;

typedef struct{
    const char*token_literal;
    List *statements;
}Program;

#endif