#ifndef OBJECT_H
#define OBJECT_H

#include "ast.h"
#include "list.h"

typedef enum ObjectTypes{
    OBJ_INT,
    OBJ_STR,
    OBJ_BOOL,
    OBJ_NULL,
    OBJ_RETURN,
    OBJ_ERROR,
    OBJ_NOT_FOUND,
    OBJ_FUNCTION,
}ObjectTypes;

typedef struct Env{
    List *store;
    struct Env *outer;
}Env;

typedef struct Object{
    ObjectTypes type;
    union{
        int i;
        char *str;
        bool b;
        struct Object *return_value;
    }value;
}object;

typedef struct Binding{
    const char* name;
    Object value;
}Binding;

//enviroment.c
Env* NewEnv(void);
Env* NewEnvEnclosed(Env* outer);
bool HasEnv(Env* env,const char* name);
object* GetEnv(Env* env,const char* name);
void SetEnv(Env* env,const char* name,object value);

#endif