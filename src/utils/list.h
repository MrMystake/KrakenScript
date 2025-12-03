#ifndef LIST_H
#define LIST_H

typedef struct List{
    void* stuff;
    struct List *next;
}List;

#endif