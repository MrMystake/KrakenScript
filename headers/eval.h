#ifndef INTERPRETER_H
#define INTERPRETER_H

int evalExpression(Expression *expr);
FactorValue evalFactor(Expression *expr);

#endif