#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  
    List * list = (List *)malloc(sizeof(List));
    assert(list != NULL);
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
  
}

void * firstList(List * list) {

    if (list == NULL || list->head == NULL){
        return NULL;
    }
    list->current = list->head;
    return (void *)list->current->data;

}

void * nextList(List * list) {
    if (list == NULL || list->head == NULL || list->current == NULL || list->current->next == NULL){
        return NULL;
    }
    list->current = list->current->next;
    return (void *)list->current->data;

}

void * lastList(List * list) { 
    if (list == NULL || list->head == NULL){
        return NULL;
    }
    list->current = list->tail;
    return (void *)list->current->data;
  
}

void * prevList(List * list) {
    if (list == NULL || list->head == NULL || list->current == NULL || list->current->prev == NULL){
        return NULL;
    }  
    list->current = list->current->prev;
    return (void *)list->current->data;
  
}

void pushFront(List * list, void * data) {
    if (list == NULL){
        return;
    }
    Node * new = createNode(data);
    if (list->head == NULL){
        list->head = new;
        list->tail = new;
      
    }
    else{
        new->next = list->head;
        list->head->prev = new;
        list->head = new;
    }
}


void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list == NULL){
      return;
    }
    Node * new = createNode(data);
    if (list->current == NULL ){
        list->head = new;
        list->tail = new;
      
    }else{
        new->next = list->current->next;
        new->prev = list->current;
        if (list->current->next == NULL){
            list->tail = new;
          
        }
      
    }
    list->current->next = new;
}


void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list == NULL || list->head == NULL || list->current == NULL){
        return NULL;
    }
    void * dato = list->current->data;
    if (list->current->prev == NULL){
        list->head = list->current->next;
        if (list->current->next != NULL){
            list->current->prev = NULL;
        }
        else{
            list->tail = NULL;
        }
      
    }
    else{
        list->current->prev->next = list->current->next;
        if (list->current->next != NULL){
            list->current->next->prev = list->current->prev;
          
        }
        else{
            list->tail = list->current->prev;
        }
      
    }
    free(list->current);

}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}