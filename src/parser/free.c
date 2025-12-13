#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdlib.h>


void FreeExpression(Expression *expr){
    if(expr == NULL){
        return;
    }
    switch(expr->type){
        case NUMBER_NODE:
        case STRING_NODE:
        case BOOLEAN_NODE:
        case VAR_IDENT:
            break;
        case:BINARY_NODE
            FreeExpression(expr->node.binary.left);
            FreeExpression(expr->node.binary.right);
            break;
    }
    free(expr);
}

void FreeStatement(Statement *st){
    if(st == NULL){
        return;
    }
    switch(st->type){
        case VAR_NODE:
            free(st->node.variable->name);
            FreeExpression(st->node.variable->value);
            free(st->node.variable);
            break;
        case RETURN_NODE:
            FreeExpression(st->node.st_return->return_value);
            free(st->node.st_return);
            break;
        case EXPRESSION_STATEMENT_NODE:
            FreeExpression(st->node.st_expr->expression);
            free(st->node.st_expr);
            break;
        case FUNCTION_NODE:
            FreeBlockStatement(st->node.func->body);
            FreeList(st->node.func->parameters);
            free(st->node.func);
            break;
        case CALL_FUNCTION_NODE:
            FreeList(st->node.call_func->arguments);
            free(st->node.call_func);
            break;
    }
    free(st);
}

void FreeList(List *list){
    return;
}

void FreeBlockStatement(List *list){
    return;
}