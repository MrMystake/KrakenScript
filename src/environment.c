#include "../headers/list.h"
#include "../headers/object.h"
#include <string.h>
#include <stdlib.h>

// Creates a new, empty environment (Env) with a global scope
// Used for the global scope.
Env* NewEnv(void){
    Env* env = malloc(sizeof(Env));
    env->store = NULL;
    env->outer = NULL;
    return env;
}

// Creates a new environment nested inside an existing one (outer).
// Used for local scopes of functions or blocks,
Env* NewEnvEnclosed(Env* outer){
    Env* env = NewEnv();
    env->outer = outer;
    return env;
}

// Checks if a variable with the given name exists in the environment.
// Returns true if the variable is found in this or any outer scope.
bool HasEnv(Env* env,const char* name){
    object* obj = GetEnv(env,name);
    if(obj->type != OBJ_NOT_FOUND)
        return true;
    else
        return false;
}

// Searches for a variable with the given name in the environment.
object* GetEnv(Env* env,const char* name){
    List* current = env->store;
    for(;current != NULL;current = current->next){
        if(current->stuff == NULL){
            continue;
        }
        Binding* bind = current->stuff;
        if(strcmp(bind->name,name)== 0){
            return bind->value;
        }
    }
    if(env->outer != NULL){
        return GetEnv(env->outer,name);
    }
    return (object){OBJ_NOT_FOUND,{.i = 0}};
}

// Adds a new variable with the given name and value to the current environment.
void SetEnv(Env* env,const char* name,object value){
    Binding* bind = malloc(sizeof(Binding));
    bind->name = name;
    bind->value = value;
    List* store = malloc(sizeof(List));
    store->stuff = bind;
    store->next = env->store;
    env->store = store;
}