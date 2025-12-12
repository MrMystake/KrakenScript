//--------------------------
//          Interpreter
//--------------------------

#include "../headers/ast.h"
#include "../headers/parser.h"
#include "../headers/token.h"
#include "../headers/Interpreter.h"
#include "../headers/object.h"
#include <stdio.h>

// Evaluates a factor node and returns its value.
FactorValue evalFactor(Expression *expr,Env *env){
    FactorValue result;
    result.type = expr->type;
    if (expr->type == NUMBER_NODE){
        result.value.number = expr->node.number.value;
    }
    else if(expr->type == STRING_NODE){
        result.value.string = expr->node.string.value;
    }
    else if(expr->type == BOOLEAN_NODE){
        result.value.boolean = expr->node.boolean.value;
    }
    return result;
}


// Evaluates an expression node recursively and returns its value.
// Handles different types of nodes (numbers, booleans, strings, 
// and binary operations) by evaluating child nodes as needed.
int evalExpression(Expression *expr){
    if (!expr) return 0;

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
