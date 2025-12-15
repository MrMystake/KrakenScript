#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Parser full program
Program* parserProgram(Parser *p){
    Program* program = malloc(sizeof(Program));
    program->statements = NULL;

    while(p->cur.type != TYPE_EOF){
        Statement *st = parserStatement(p);
        if(st != NULL){
            program->statements = list_append_value(program->statements,st);
        }
        else{
            fprintf(stderr,"Parser Error:unexpected token %s",p->cur.start);
            next(p);
        }
    }
    return program;
}