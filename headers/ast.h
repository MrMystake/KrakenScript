#ifndef AST_H
#define AST_H


#include "lexer.h"
#include "list.h"
#include "token.h"


typedef struct Statement Statement;
typedef struct StatementBlock StatementBlock;
typedef struct Expression Expression;

//-------------------------------------
//            Expresion
//-------------------------------------



typedef enum ExpressionNodeType{
    EXPRESSION_NODE,
    EXPRESSION_STATEMENT_NODE,
    NUMBER_NODE,
    BOOLEAN_NODE,
    STRING_NODE,
    BINARY_NODE,
    VAR_IDENT,
}ExpressionNodeType;

//struct for node types
typedef struct {
    ExpressionNodeType type;
    union{
        int number;
        const char* string;
        bool boolean;
    }value;
}FactorValue;

typedef struct ExpressionStatement{
    token token;
    Expression *expression;
}ExpressionStatement;

typedef struct {
    token token;
    int value;
}NumberLiteral;

typedef struct{
    token token;
    bool value;
}BooleanLiteral;

typedef struct{
    token token;
    const char* value;
}StringLiteral;

typedef struct{
    token token;
    TokenType operator;
    Expression *left;
    Expression *right;
}BinaryExpr;

typedef struct{
    token token;
    Expression *conditional;
    StatementBlock *if_block;
    StatementBlock *else_block;
}ExpressionIf;

typedef struct{
    token token;
    const char *name;
}VarName;

typedef struct Expression{
    token token;
    ExpressionNodeType type;
    const char * token_literal;
    union{
        NumberLiteral number;
        BooleanLiteral boolean;
        StringLiteral string;
        BinaryExpr binary;
        ExpressionIf exprIf;
        VarName varName;
    }node;
}Expression;

//-------------------------------------
//           Statement
//-------------------------------------


typedef enum StatementNodeType{
    PROGRAM_NODE,
    STATEMENT_NODE,
    BLOCK_NODE,
    VAR_NODE,
    RETURN_NODE,
}StatementNodeType;

typedef struct StatementBlock{
    token *token;
    List *statements;
}StatementBlock;

typedef struct{
    token *token;
    Expression *return_value;
}ReturnStatement;


typedef struct{
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

typedef struct Statement{
    token *token;
    StatementNodeType type;
    union{
        StatementBlock block;
        ReturnStatement st_return;
        Variable variable;
        FunctionStatement func;
        CallFunctionStatement call_func;
        Program program;
    }node;
}Statement;

#endif