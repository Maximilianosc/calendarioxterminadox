/**
 MIT License
 
 Copyright (c) 2018 Matias Barrientos.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "List.h"
#include <stdlib.h>
#include <assert.h>

typedef struct Node Node;

static Node * createNode(const void * data);

struct Node {
    /*! Puntero al dato */
    const void * data;
    
    /*! Puntero al siguiente nodo */
    Node * next;
    
    /*! Puntero al anterior nodo */
    Node * prev;
};

struct List {
    /*! Puntero al incio (cabeza) de la lista */
    Node * head;
    
    /*! Puntero al final (cola) de la lista */
    Node * tail;
    
    /*! Punteor para poder recorrer la lista */
    Node * current;
    
    /*! Cantidad de elemento en la lista */
    long count;
};

static Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL); // No hay memoria para reservar el Nodo.
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List * new = (List *)malloc(sizeof(List));
    assert(new != NULL); // No hay memoria para reservar la Lista.
    new->head = new->tail = new->current = NULL;
    new->count = 0;
    return new;
}

long listCount(List * list) {
    assert(list != NULL); // list no puede ser NULL.
   
    if (list->head == NULL) return 0;
   
    return list->count;
}

int emptyList(List * list) {
    assert(list != NULL); // list no puede ser NULL.
    return list->count == 0;
}

void * firstList(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return NULL;
    
    list->current = list->head;
    
    return (void *)list->current->data;
}

void * nextList(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL || list->current == NULL || list->current->next == NULL) return NULL;
    
    list->current = list->current->next;
    
    return (void *)list->current->data;
}

void * lastList(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return NULL;
   
    list->current = list->tail;
    
    return (void *)list->current->data;
}

void * prevList(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
    
    list->current = list->current->prev;
    
    return (void *)list->current->data;
}

void pushFront(List * list, const void * data) {
    assert(list != NULL); // list no puede ser NULL.
    
    Node * new = createNode(data);
    
    if (list->head == NULL) {
        list->tail = new;
    } else {
        new->next = list->head;
        list->head->prev = new;
    }
    
    list->head = new;
    list->count += 1;
}

void pushBack(List * list, const void * data) {
    assert(list != NULL); // list no puede ser NULL.
    
    Node * new = createNode(data);
    
    if (list->head == NULL) {
        list->head = new;
    } else {
        list->tail->next = new;
        new->prev = list->tail;
    }
    
    list->tail = new;
    list->count += 1;
}

void pushCurrent(List * list, const void * data) {
    assert(list != NULL); // list no puede ser NULL.
    
    if (list->current == NULL) return;
    
    Node * new = createNode(data);
    
    new->next = list->current->next;
    new->prev = list->current;
    
    if (list->current->next != NULL) {
        list->current->next->prev = new;
    }
    
    list->current->next = new;
    
    if (list->current == list->tail) {
        list->tail = new;
    }
        
    list->count += 1;
}

void * popFront(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return NULL;
    
    Node * aux = list->head;
    
    void * data = (void *)aux->data;
    
    if (list->head == list->tail) {
        list->tail = list->head = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    
    free(aux);
   
    list->count -= 1;
    
    return data;
}

void * popBack(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return NULL;
    
    Node * aux = list->tail;

    void * data = (void *)aux->data;

    if (list->tail == list->head) {
        list->tail = list->head = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    
    free(aux);
    
    list->count -= 1;
    
    return data;
}

void * popCurrent(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL || list->current == NULL) return NULL;
    
    Node * aux = list->current;
    
    if (list->current == list->head) {
        return popFront(list);
    } else if (list->current == list->tail) {
        return popBack(list);
    } else {
        if (aux->next != NULL) {
            aux->next->prev = aux->prev;
        }
        
        if (aux->prev != NULL) {
            aux->prev->next = aux->next;
        }
    }

    void * data = (void *)aux->data;
    
    list->current = aux->next;
    
    free(aux);
    
    list->count -= 1;
    
    return data;
}

void removeAllList(List * list) {
    assert(list != NULL); // list no puede ser NULL.

    while (list->head != NULL) {
        popFront(list);
    }
}

