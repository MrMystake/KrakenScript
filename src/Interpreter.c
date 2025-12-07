#include "../headers/ast.h"
#include "../headers/parser.h"
#include "../headers/token.h"
#include <stdio.h>

int evalExpression(Expression *expr){
    if (!expr) return 0;

    if(expr->type == NUMBER_NODE){
        return expr->node.number.value;
    }

    if(expr->type == BINARY_NODE){
        switch(expr->token.type){
            case TYPE_PLUS:
                return evalExpression(expr->node.binary.left) + evalExpression(expr->node.binary.right);
            case TYPE_MINUS:
                return evalExpression(expr->node.binary.left) - evalExpression(expr->node.binary.right);
            case TYPE_STAR:
                return evalExpression(expr->node.binary.left) * evalExpression(expr->node.binary.right);
            case TYPE_SLASH:
                return evalExpression(expr->node.binary.left) / evalExpression(expr->node.binary.right);
        }
    }

}