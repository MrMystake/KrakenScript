#ifndef LIST_H
#define LIST_H

typedef struct List{
    void* stuff;
    struct List *next;
}List;

List* list_append_value(List *list,void*stuff);
int list_count(List *list);

#endif