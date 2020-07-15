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

#ifndef List_h
#define List_h

typedef struct List List;

/**
 Crea un nuevo puntero de tipo List.

 @return Puntero a la nueva List.
 */
List * createList(void);

/**
 Devuele el primer dato de la List.
 
 Complejidad: O(1)

 @param list Puntero a la List.
 @return Puntero al dato contenido en la cabeza.
 */
void * firstList(List * list);

/**
 Devuele el siguiente dato de la List.
 
 Complejidad: O(1)
 
 @param list Puntero a la List.
 @return Puntero al dato.
 
 Ejemplo:
 
 @code
 void * data = firstList(list);
 
 while (data != NULL) {
    // Aqui puede manipular el dato o imprimirlo.
    data = nextList(list);
 }
 */
void * nextList(List * list);

/**
 Devuelve el ultimo dato de la List.
 
 Complejidad: O(1)

 @param list Puntero a la List.
 @return Puntero al dato.
 */
void * lastList(List * list);

/**
 Devuele el anterior dato de la List.
 
 Complejidad: O(1)
 
 @param list Puntero a la List.
 @return Puntero al dato.
 
 @code
 void * data = lastList(list);
 
 while (data != NULL) {
     // Aqui puede manipular el dato o imprimirlo.
     data = prevList(list);
 }
 */
void * prevList(List * list);

/**
 Cantidad de elementos en la List.
 
 Complejidad: O(1)

 @param list Puntero a la List.
 @return Cantidad de elementos en la List.
 */
long listCount(List * list);

/**
 Prueba si la List está vacía.
 
 Complejidad: O(1)
 
 @param list Puntero a la List.
 @return 1 (true) si y solo si la List no contiene elementos; 0 (false) lo contrario.
 */
int emptyList(List * list);

/**
 Inserta un elemento en al inicio de la List.
 
 Complejidad: O(1)

 @param list Puntero a la List.
 @param data Puntero al dato que se quiere guardar.
 */
void pushFront(List * list, const void * data);

/**
 Inserta un elemento al final de la lista.
 
 Complejidad: O(1)

 @param list Puntero a la List.
 @param data Puntero al dato que se quiere guardar.
 */
void pushBack(List * list, const void * data);

/**
 Inserta un elemento despues del current. El current se actualiza cuando se reccore la lista con las funciones firstList, etc.
 
 Complejidad: O(1)

 @param list Puntero a la List.
 @param data Puntero al dato que se quiere guardar.
 */
void pushCurrent(List * list, const void * data);

/**
 Elimina el nodo del inicio de la List.
 
 Complejidad: O(1)

 @param list Puntero a la List.
 @return Puntero del dato eliminado.
 */
void * popFront(List * list);

/**
 Elimina el nodo final de la List.
 
 Complejidad: O(1)

 @param list Puntero a la List.
 @return Puntero del dato eliminado.
 */
void * popBack(List * list);

/**
 Elimina el nodo en donde se encuentre el current, actualiza el current al siguiente de este.
 
 Complejidad: O(1)

 @param list Puntero a la List.
 @return Puntero del dato eliminado.
 */
void * popCurrent(List * list);

/**
 Elimina todos los nodos de la List.
 
 Complejidad: O(n)

 @param list Puntero a la List.
 */
void removeAllList(List * list);

#endif /* List_h */
