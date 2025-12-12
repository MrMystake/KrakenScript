#include "../headers/lexer.h"
#include "../headers/parser.h"
#include <stdio.h>
#include <string.h>

void assert_rus(int condition, const char* msg) {
    if (!condition) {
        printf("[НЕ ПРОШЛО] %s\n", msg);
    } else {
        printf("[УСПЕХ] %s\n", msg);
    }
}

// Получение первого элемента списка
Statement* first_statement(List *list) {
    if (list == NULL) return NULL;
    return (Statement*)list->stuff;
}

// Подсчёт элементов списка
int list_len(List *list) {
    int count = 0;
    for (List *l = list; l != NULL; l = l->next) count++;
    return count;
}

// Проверка var declaration
void test_var_declaration() {
    const char *source = "var x = 42;";
    lexer lex; LexerInit(&lex, source);
    Parser p; ParserInit(&p, &lex);
    Program *program = parserProgram(&p);  // возвращает Program*

    Statement *st = first_statement(program->statements);
    assert_rus(st->type == VAR_NODE, "Ожидался тип VAR_NODE");
    assert_rus(strcmp(st->node.variable->name->name, "x") == 0, "Имя переменной должно быть 'x'");
    assert_rus(st->node.variable->value->type == NUMBER_NODE, "Значение переменной должно быть NUMBER_NODE");
    assert_rus(st->node.variable->value->node.number.value == 42, "Значение переменной должно быть 42");
}

// Проверка return
void test_return_statement() {
    const char *source = "return 10;";
    lexer lex; LexerInit(&lex, source);
    Parser p; ParserInit(&p, &lex);
    Program *program = parserProgram(&p);

    Statement *st = first_statement(program->statements);
    assert_rus(st->type == RETURN_NODE, "Ожидался тип RETURN_NODE");
    assert_rus(st->node.st_return->return_value->node.number.value == 10, "Возвращаемое значение должно быть 10");
}

// Проверка функции
void test_function_declaration() {
    const char *source = "func add(a, b) { return a + b; }";
    lexer lex; LexerInit(&lex, source);
    Parser p; ParserInit(&p, &lex);
    Program *program = parserProgram(&p);

    Statement *st = first_statement(program->statements);
    assert_rus(st->type == FUNCTION_NODE, "Ожидался тип FUNCTION_NODE");
    assert_rus(strcmp(st->node.func->name, "add") == 0, "Имя функции должно быть 'add'");
    assert_rus(list_len(st->node.func->parameters) == 2, "Функция должна иметь 2 параметра");
}

// Проверка вызова функции
void test_call_function() {
    const char *source = "add(1, 2);";
    lexer lex; LexerInit(&lex, source);
    Parser p; ParserInit(&p, &lex);
    Program *program = parserProgram(&p);

    Statement *st = first_statement(program->statements);
    assert_rus(st->type == CALL_FUNCTION_NODE, "Ожидался тип CALL_FUNCTION_NODE");
    assert_rus(strcmp(st->node.call_func->func_name, "add") == 0, "Имя вызываемой функции должно быть 'add'");
    assert_rus(list_len(st->node.call_func->arguments) == 2, "Должно быть 2 аргумента");
}

// Проверка арифметики и скобок
void test_arithmetic() {
    const char *source = "(1 + 2) * 3;";
    lexer lex; LexerInit(&lex, source);
    Parser p; ParserInit(&p, &lex);
    Program *program = parserProgram(&p);

    Statement *st = first_statement(program->statements);
    assert_rus(st->type == EXPRESSION_STATEMENT_NODE, "Ожидался тип EXPRESSION_STATEMENT_NODE");
    Expression *expr = st->node.st_expr->expression;
    assert_rus(expr->type == BINARY_NODE, "Главный узел должен быть BINARY_NODE");
}

// Проверка булевых значений
void test_boolean() {
    const char *source = "var b = true;";
    lexer lex; LexerInit(&lex, source);
    Parser p; ParserInit(&p, &lex);
    Program *program = parserProgram(&p);

    Statement *st = first_statement(program->statements);
    assert_rus(st->node.variable->value->type == BOOLEAN_NODE, "Значение должно быть BOOLEAN_NODE");
    assert_rus(st->node.variable->value->node.boolean.value == true, "Значение должно быть true");
}

int main() {
    printf("=== Тестирование парсера ===\n");
    test_var_declaration();
    test_return_statement();
    test_function_declaration();
    test_call_function();
    test_arithmetic();
    test_boolean();
    printf("=== Все тесты завершены ===\n");
    return 0;
}
