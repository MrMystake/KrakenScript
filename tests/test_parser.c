#include "../headers/lexer.h"
#include "../headers/parser.h"
#include "../headers/ast.h"
#include <stdio.h>
#include <stdlib.h>

// Безопасная печать Expression
void PrintExpression(Expression *expr){
    if(!expr){
        printf("NULL Expression\n");
        return;
    }

    switch(expr->type){
        case NUMBER_NODE:
            printf("Number: %d\n", expr->node.number.value);
            break;
        case STRING_NODE:
            printf("String: %s\n", expr->node.string.value);
            break;
        case BOOLEAN_NODE:
            printf("Boolean: %s\n", expr->node.boolean.value ? "true" : "false");
            break;
        case VAR_IDENT:
            printf("Variable: %s\n", expr->node.ident.name);
            break;
        case BINARY_NODE:
            printf("Binary Expression: operator %d\n", expr->node.binary.operator);
            printf("Left -> "); PrintExpression(expr->node.binary.left);
            printf("Right -> "); PrintExpression(expr->node.binary.right);
            break;
        default:
            printf("Unknown Expression Type\n");
    }
}

// Безопасная печать Statement
void PrintStatement(Statement *stmt){
    if(!stmt){
        printf("NULL Statement\n");
        return;
    }

    printf("=== Statement ===\n");
    switch(stmt->type){
        case VAR_NODE:
            printf("Var Declaration: %s\n", stmt->node.variable->name->name);
            printf("Value -> "); 
            PrintExpression(stmt->node.variable->value);
            break;
        case EXPRESSION_STATEMENT_NODE:
            printf("Expression Statement:\n");
            PrintExpression(stmt->node.st_expr->expression);
            break;
        case RETURN_NODE:
            printf("Return Statement:\n");
            PrintExpression(stmt->node.st_return->return_value);
            break;
        case BLOCK_NODE:
            printf("Block Statement with %d statements\n", list_count(stmt->node.block->statements));
            for(List *l = stmt->node.block->statements; l != NULL; l = l->next){
                PrintStatement((Statement*)l->stuff);
            }
            break;
        case FUNCTION_NODE:
            printf("Function Statement: %s\n", stmt->node.func->name);
            break;
        default:
            printf("Unknown Statement Type\n");
    }
}

int main(){
    const char* code = 
        "var x = 42;\n"
        "var y = x + 13;\n"
        "func add(a, b) {var a = 10}\n"
        "func add(c,d) {return x + y}\n";

    // Инициализация лексера
    lexer l;
    LexerInit(&l, code);

    // Инициализация парсера
    Parser p;
    ParserInit(&p, &l);

    Statement *stmt;
    int safety = 0; // ограничитель на случай зацикливания
    while((stmt = parserStatement(&p)) != NULL && safety++ < 100){
        PrintStatement(stmt);
        FreeStatement(stmt);
    }

    if(safety >= 100) printf("Loop terminated due to safety limit\n");


    return 0;
}
