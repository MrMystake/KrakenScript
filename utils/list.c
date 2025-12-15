#include "../headers/list.h"
#include <stdio.h>
#include <stdlib.h>

// Appends a value to the end of a list.
// Takes a pointer to the list and the value to add,
// then updates the list structure accordingly.

List* list_append_value(List *list,void*stuff){
    List *node = malloc(sizeof(List));
    node->stuff = stuff;
    node->next = NULL;

    if(list ==  NULL){
        return node;
    }

    List *indicate = list;
    while(indicate->next != NULL) indicate = indicate->next;
    indicate->next = node;

    return list;
}

// Returns the number of elements in a list.
// Iterates through the list and counts all items.

int list_count(List *list){
    int list_count;
    List *indicate = list;
    for(list_count = 0;indicate != NULL;list_count++) indicate = indicate->next;
    return list_count;
}

void free_list(List *list){
    while(list != NULL){
        List *next = list->next;
        free(list);
        list = next;
    }
}