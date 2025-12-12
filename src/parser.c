//--------------------------
//          Parser
//--------------------------

#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//additional functions
void next(Parser *p){
    p->cur = p->next;
    p->next = NextToken(p->lex);
}

int match(Parser *p, TokenType type){
    if (p->cur.type == type) {
        return 1;
    }
    return 0;
}

bool StringBool(Parser *p){
    if (strcmp(p->cur.start,"true") == 0) return true;
    if (strcmp(p->cur.start,"false") == 0) return false;
    return false;
}

//create Parser
void ParserInit(Parser *p,lexer *lex){
    p->lex = lex;
    p->cur = NextToken(lex);
    p->next = NextToken(lex);
}


// Parses a full expression.
// This is the top-level expression parser that handles operator
// precedence by calling lower-level parsers (sum, term, factor).
// It returns the final expression tree representing the entire expression.
Expression* parserExpression(Parser *p){
    return parserSum(p);
}


// Parses the smallest unit of an expression (a "factor").
// A factor can be a number, string, boolean, identifier, or
// an expression inside parentheses. This function reads the
// current token and returns the corresponding expression node.
Expression* parserFactor(Parser *p){
    if(match(p,TYPE_NUMBER)){
        Expression *node = malloc(sizeof(Expression));
        node->token = p->cur;
        node->token_literal = p->cur.start;
        node->type = NUMBER_NODE;
        node->node.number.token = p->cur;
        node->node.number.value = atoi(p->cur.start);

        next(p);
        return node;
    }
    else if(match(p,TYPE_STRING)){
        Expression *node = malloc(sizeof(Expression));
        node->token = p->cur;
        node->token_literal = p->cur.start;
        node->type = STRING_NODE;
        node->node.string.token = p->cur;
        node->node.string.value = p->cur.start;

        next(p);
        return node;
    }
    else if(match(p,TYPE_TRUE) || match(p,TYPE_FALSE)){
        Expression *node = malloc(sizeof(Expression));
        node->token = p->cur;
        node->token_literal = p->cur.start;
        node->type = BOOLEAN_NODE;
        node->node.boolean.token = p->cur;
        node->node.boolean.value = StringBool(p);

        next(p);
        return node;
    }
    else if(match(p,TYPE_LPAREN)){
        next(p);
        Expression *node = parserExpression(p);
        match(p,TYPE_RPAREN);

        next(p);
        return node;
    }
}


// Parses a term in an expression.
// A term usually handles multiplication, division, and modulo.
// It takes the left factor, checks for * / % operators,
// and builds a binary expression tree while such operators appear.
Expression* parserTerm(Parser *p){
    Expression *left = parserFactor(p);

    while(match(p,TYPE_STAR) || match(p,TYPE_SLASH)){
        Expression *parent = malloc(sizeof(Expression));

        parent->token = p->cur;
        parent->token_literal = p->cur.start;
        parent->type = BINARY_NODE;
        parent->node.binary.token = p->cur;
        parent->node.binary.operator = p->cur.type;
        next(p);

        Expression *right = parserFactor(p);
        parent->node.binary.left = left;
        parent->node.binary.right = right;
        left = parent;
    }
    return left;
}


//// Parses a sum-level expression.
// This handles addition and subtraction. It first parses a term,
// then checks for + or - operators and builds a binary expression
// tree while these operators are present.
Expression* parserSum(Parser *p){
    Expression *left = parserTerm(p);

    while(match(p,TYPE_PLUS) || match(p,TYPE_MINUS)){
        Expression* parent = malloc(sizeof(Expression));

        parent->token = p->cur;
        parent->token_literal = p->cur.start;
        parent->type = BINARY_NODE;
        parent->node.binary.token = p->cur;
        parent->node.binary.operator = p->cur.type;
        next(p);

        Expression* right = parserTerm(p);
        parent->node.binary.left = left;
        parent->node.binary.right = right;
        left = parent;
    }
    return left;
}


//var ident = value
Statement* parserVar(Parser *p){
    token VarToken = p->cur;
    if(match(p,TYPE_VAR)){
        next(p);
    }
    VarName *ident = malloc(sizeof(VarName));
    if(match(p,TYPE_IDENT)){
        ident->token = p->cur;
        ident->name = p->cur.start;
        next(p);
    }
    else{
        fprintf(stderr,"Error:After var must be ident");
        free(ident);
        return NULL;
    }
    if(match(p,TYPE_ASIGN)){
        next(p);
    }
    else{
        fprintf(stderr,"Error:After ident must be asign");
        free(ident);
        return NULL;
    }
    Expression* value = parserExpression(p);

    Variable* var = malloc(sizeof(Variable));
    
    var->name = ident;
    var->value = value;

    Statement* st_var = malloc(sizeof(Statement));
    st_var->token = VarToken;
    st_var->type = VAR_NODE;
    st_var->node.variable = var;

    if(match(p,TYPE_EOL))
        return st_var;
}
//return value
Statement* parserReturn(Parser *p){
    ReturnStatement* ret = malloc(sizeof(ReturnStatement));
    token ReturnToken = p->cur;
    if(match(p,TYPE_RETURN)){
        next(p);
    }
    Expression* value = parserExpression(p);
    ret->token = p->cur;
    ret->return_value = value;

    Statement* st_return = malloc(sizeof(Statement));
    st_return->token = ReturnToken;
    st_return->type = RETURN_NODE;
    st_return->node.st_return = ret;

    if(match(p,TYPE_EOL))
        return st_return;
}


Statement* parserStatement(Parser *p){
    if(match(p,TYPE_VAR)){
        return parserVar(p);
    }
    else if(match(p,TYPE_RETURN)){
        return parserReturn(p);
    }
    else{
        return parserExprStatement(p);
    }
}
//x + x ;name()
Statement* parserExprStatement(Parser *p){
    Expression* expression = parserExpression(p);

    ExpressionStatement* ExprState = malloc(sizeof(ExpressionStatement));
    ExprState->token = p->cur;
    ExprState->expression = expression;

    Statement* st = malloc(sizeof(Statement));
    st->token = p->cur;
    st->type = EXPRESSION_STATEMENT_NODE;
    st->node.st_expr = ExprState;

    return st;
}

StatementBlock* parserBlockStatement(Parser *p){
    if (!match(p, TYPE_LBRACE)) {
        return NULL;
    }
    StatementBlock* block = malloc(sizeof(StatementBlock));
    token token = p->cur;
    block->token = token;
    block->statements = NULL;

    Statement* st;
    for(;p->cur.type != TYPE_EOF && p->cur.type != TYPE_RBRACE ;){
        st = parserStatement(p);
        if(st != NULL){
            block->statements = list_append_value(block->statements,st);
        }
        next(p);
    }
    if(match(p,TYPE_RBRACE)){
        next(p);
    }

    return block;
}
// func name(parametrs){
//  body}
Statement* parserFunction(Parser *p){
    FunctionStatement* func = malloc(sizeof(FunctionStatement));
    StatementBlock* block = malloc(sizeof(StatementBlock));
    token Ftoken = p->cur;

    if(match(p,TYPE_FUNCTION)){
        func->token = Ftoken;
        next(p);
    }

    if(match(p,TYPE_IDENT)){
        func->name = p->cur.start;
        next(p);
    }

    if(match(p,TYPE_LPAREN)){
        next(p);
        func->parameters = parserFuncParameters(p);
    }
    else{
        fprintf(stderr,"Error:Expected (\n");
        return NULL;
    }

    if(!match(p,TYPE_RPAREN)){
        func->body = parserBlockStatement(p);
    }
    else{
        fprintf(stderr,"Error:Expected (\n");
        return NULL;
    }

    Statement *st = malloc(sizeof(Statement));
    st->token = Ftoken;
    st->type = FUNCTION_NODE;
    st->node.func = func;

    return st;
}
List* parserFuncParameters(Parser *p){
    List* params = NULL;
    if(match(p,TYPE_RPAREN)){
        next(p);
        return params;
    }
    if(!match(p,TYPE_IDENT)){
        fprintf(stderr,"Error: expected parameter name\n");
        return NULL;
    }
    params = list_append_value(params,p->cur.start);
    next(p);
    while(match(p,TYPE_COMMA)){
        next(p);
        if(!match(p,TYPE_IDENT)){
            fprintf(stderr,"Error: expected identifier after ','\n");
            return NULL;
        }
        params = list_append_value(params,p->cur.start);
        next(p);
    }
    if(match(p,TYPE_RPAREN)){
        fprintf(stderr, "Error: expected ')'\n");
        return NULL;
    }
    return params;
}
//name(num_1,num_2)
Statement* parserCallFunc(Parser *p){
    token CFtoken = p->cur;
    CallFunctionStatement* call_func = malloc(sizeof(CallFunctionStatement));
    Statement *st = malloc(sizeof(Statement));

    if(match(p,TYPE_IDENT)){
        call_func->token = CFtoken;
        call_func->func_name = p->cur.start;
        next(p);
    }
    else{
        fprintf(stderr,"Error: expected parameter name\n");
        return NULL;
    }

    if(match(p,TYPE_LPAREN)){
        next(p);
        call_func->arguments = parserFuncParameters(p);
    }
    else{
        fprintf(stderr,"Error:Expected (\n");
        return NULL;
    }
    st->token = CFtoken;
    st->type = CALL_FUNCTION_NODE;
    st->node.call_func = call_func;
    
    return st;
}

Program* parserProgram(Parser *p){
    Program* program = malloc(sizeof(Program));
    Statement *st;
    program->statements = NULL;
    for(;p->cur.type != TYPE_EOF;){
        st = parserStatement(p);
        if(st != NULL){
            program->statements = list_append_value(program->statements,st);
        }
    }
    return program;
}