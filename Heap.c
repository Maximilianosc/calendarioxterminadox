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


#include "Heap.h"
#include <stdlib.h>
#include <assert.h>

#define PARENT(i) (i - 1) / 2
#define LEFT(i) 2 * i + 1
#define RIGHT(i) 2 * i + 2

struct Heap {
    /*! Arreglo de punteros de datos tipo void */
    const void ** heapArray;
    
    /*! Cantidad de elementos no nulos */
    long count;
    
    /*! Tamaño del arreglo */
    long size;
    
    /*! Función comparar */
    HeapCompareCallBack compare;
};

/**
 Encargada de ordenar el arreglo del heap con respecto a la comparacion.

 @param heap Puntero a la struct Heap.
 @param i Posicion en que parte el ordenamiento del arreglo.
 */
static void heapify(Heap * heap, long i) {
    long smallest = i;
    
    if (LEFT(i) < heap->count && heap->compare(heap->heapArray[LEFT(i)], heap->heapArray[i]) < 0) {
        smallest = LEFT(i);
    }
    
    if (RIGHT(i) < heap->count && heap->compare(heap->heapArray[RIGHT(i)], heap->heapArray[smallest]) < 0) {
        smallest = RIGHT(i);
    }
    
    if (smallest != i) {
        const void * tmp = heap->heapArray[i];
        heap->heapArray[i] = heap->heapArray[smallest];
        heap->heapArray[smallest] = tmp;
        heapify(heap, smallest);
    }
}

Heap * createHeap(HeapCompareCallBack compare, long size) {
    Heap * new = (Heap *)malloc(sizeof(Heap));
    
    assert(new != NULL); // Se verifica que no sea null.
    
    new->heapArray = (const void **)malloc(sizeof(const void *) * size);
    new->size = size;
    new->count = 0;
    new->compare = compare;
    
    return new;
}

void pushHeap(Heap * heap, const void * data) {
    assert(heap != NULL); // El heap no puede ser null.
    assert(heap->heapArray != NULL); // El heapArray no puede ser null.
    
    if (heap->count == heap->size) {
        heap->size = heap->size * 2 + 1;
        heap->heapArray = (const void **)realloc(heap->heapArray, heap->size * sizeof(const void *));
        assert(heap->heapArray != NULL); // No hay memoria para relocalizar el arreglo.
    }
    
    long i = heap->count;
    
    while (i > 0 && heap->compare(data, heap->heapArray[PARENT(i)]) < 0) {
        heap->heapArray[i] = heap->heapArray[PARENT(i)];
        i = PARENT(i);
    }
    
    heap->heapArray[i] = data;
    heap->count += 1;
}

void * popHeap(Heap * heap) {
    assert(heap != NULL); // El heap no puede ser null.
    assert(heap->heapArray != NULL); // El heapArray no puede ser null.
    
    if (heap->count == 0) return NULL;
    
    void * data = (void *)heap->heapArray[0];
    
    heap->count -= 1;
    
    heap->heapArray[0] = heap->heapArray[heap->count];
   
    heapify(heap, 0);
    
    return data;
}

void * peekHeap(Heap * heap) {
    assert(heap != NULL); // El heap no puede ser null.
    assert(heap->heapArray != NULL); // El heapArray no puede ser null.
    
    if (heap->count == 0) return NULL;
    
    return (void *)heap->heapArray[0];
}

long heapCount(Heap * heap) {
    assert(heap != NULL); // El heap no puede ser null.
    
    if (heap->heapArray == NULL) return 0;
    
    return heap->count;
}

void removeAllHeap(Heap * heap) {
    assert(heap != NULL); // El heap no puede ser null.
    
    if (heap->heapArray != NULL) {
        free(heap->heapArray);
        heap->heapArray = NULL;
        heap->count = 0;
    }
}
