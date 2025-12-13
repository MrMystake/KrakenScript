#include "../headers/lexer.h"
#include "../headers/ast.h"
#include "../headers/token.h"
#include "../headers/list.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parses a full expression.
// This is the top-level expression parser that handles operator
// precedence by calling lower-level parsers (sum, term, factor).
// It returns the final expression tree representing the entire expression.
Expression* parserExpression(Parser *p){
    return parserSum(p);
}