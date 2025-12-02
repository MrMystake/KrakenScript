#ifndef AST_H
#define AST_H

#include "lexer.h"

//expr типы значений

typedef enum NodeTypes{
    PROGRAM_NODE,                   //узел программы (вся программа целиков)
    EXPRESSION_NODE,                //узел выражения (логическое,арифмитическое и тд)
    EXPRESSION_STATEMENT_NODE,      //узел оператора выражения (х+1)
    RETURN_STATEMENT_NODE,          //узел оператора return
    LET_STATEMENT_NODE,             //узел оператора обьявления переменной
    INTEGER_LITERAL_NODE,           //узел числового литерала (p.s просто число)
    BOLLEAN_LITERAL_NODE,           //узел логического литерала (True or False)
    BLOCK_STATEMENTS_NODE,          //узел блока операторов (несколько оперантов заключенных в {}выполняють как 1 блок)
}TypeExpr;

typedef struct Expression{
    token *token;
    const char *token_literal;
    void *node;
}Expression;

typedef struct NumberLiteral{
    token *token;
    int value;
}NumberLiteral;

typedef struct VariableExpr{
    token *token;
    int value;
}VariableExpr;

typedef struct BinaryExpr{
    token *token;
    const char* oper; 
    Expression *left;
    Expression *right;
}BinaryExpr;


typedef struct AssignExpr{
    token *token;
    const char *assign;
    Expression *value;

}AssignExpr;

typedef struct IfStmt{

}IfStmt;