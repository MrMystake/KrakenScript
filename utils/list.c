#include "../headers/list.h"
#include <stdio.h>
#include <stdlib.h>

List list_append_value(List *list,void*stuff){
    List *node = malloc(sizeof(List));
    node->stuff = stuff;
    node->next = NULL;

    if(list ==  NULL){
        return *node;
    }

    List *indicate = list;
    while(indicate->next != NULL) indicate = indicate->next;
    indicate->next = node;

    free(node);
    return *list;
}

int list_count(List *list){
    int list_count;
    List *indicate = list;
    for(list_count = 0;indicate != NULL;list_count++) indicate = indicate->next;
    return list_count;
}