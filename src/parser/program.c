#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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