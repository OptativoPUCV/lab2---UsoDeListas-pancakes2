#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "arraylist.h"
#include "stack.h"

//#include "exercises.h"

//Funciones auxiliares que puedes utilizar para debuggear tus ejercicios
//NO MODIFICAR
void imprime_lista(List *L) {
   int *dato;
   dato = (int*)first(L);
   printf("[");
   while(dato != NULL) {
      printf("%d ", *dato);
      dato = (int*)next(L);
   }
   printf("]\n");

}

//Ojo que la pila se vacía al imprimir y se imprime en orden inverso
//NO MODIFICAR
void imprime_y_vacia_pila(Stack *P) {
   void *dato;
   printf("[");
   while((dato = pop(P)) != NULL) {
      printf("%d ", *(int*)dato);
   }
   printf("]\n");
}

/* Ejericio N°1
Se asigna *list como el puntero al primer elemento de 'List' y checkeamos la asignación de memoria. Luego iteramos 10 veces y en cada iteración se asigna memoria para un puntero a un entero que luego se asigna al final de la lista con valor 'i', que sería del 1 al 10.
*/

List* crea_lista() {
    List* list = create_list();
    if (list == NULL) {
        return NULL;
    }

    for (int i = 1; i <= 10; i++) {
        int* data = malloc(sizeof(int));
        if (data == NULL) {
            return NULL;
        }
        *data = i;
        pushBack(list, data);
    }

    return list;
}

/* Ejercicio N°2
Iteramos todos los punteros de la lista (elementos) y los iriamos
sumando a nuestra variable local 'sum', la cual llevaría el recuento
de la suma de los elementos para luego retornalo.
*/

int sumaLista(List *L) {
    int sum = 0;
    for (void* data = first(L); data != NULL; data = next(L)) {
        sum += *(int*)data;
    }
    return sum;
}

/* Ejercicio N°3
La función itera todos los punteros (elementos) de la lista, hasta que
data apunte a NULL (llegamos al final del arreglo), por cada iteración
se compara el valor del puntero *data con el número a eliminar, de ser
así se elimina el elemento actual.
*/

void eliminaElementos(List *L, int elem) {
    for (void* data = first(L); data != NULL; data = next(L)) {
        if (*(int*)data == elem) {
            popCurrent(L);
        }
    }
}

/* Ejercicio N°4
La función es bastante simple, iteramos todo el stack y lo copiamos a nuestro stack auxiliar por medio de las funciones básicas.
Este estaría alrevéz por como funcionarían los stacks, por lo que para
tener el orden original hay que nuevamente, iterar el stack pero ahora
el aux y ahora si los insertamos a ambos stacks P1 y P2 con push().
*/

void copia_pila(Stack* P1, Stack* P2) {
    Stack* aux = create_stack();
    while (top(P1) != NULL) {
        push(aux, pop(P1));
    }
    while (top(aux) != NULL) {
        void* data = pop(aux);
        push(P1, data);
        push(P2, data);
    }
    free(aux);
}

/* Ejercicio N°5
La función simula un hashmap con un arreglo que almacenaría los códigos
ASCII de los caracteres que necesitamos.
Comparamos los caracteres de la cadena con los códigos ASCII de los caracteres y ejectamos la lógica que necesitamos.
*/

int parentesisBalanceados(char *cadena) {
    char map[128];
    map['('] = ')';
    map['['] = ']';
    map['{'] = '}';

    Stack* stack = create_stack();
    for (int i = 0; i < strlen(cadena); i++) {
        if (cadena[i] == '(' || cadena[i] == '[' || cadena[i] == '{') {
            push(stack, &cadena[i]);
        } else if (cadena[i] == ')' || cadena[i] == ']' || cadena[i] == '}') {
            if (top(stack) == NULL) {
                free(stack);
                return 0;
            }
            char open = *(char*)pop(stack);
            if (map[(int)open] != cadena[i]) {
                free(stack);
                return 0;
            }
        }
    }
    int balanced = top(stack) == NULL ? 1 : 0;
    free(stack);
    return balanced;
}
