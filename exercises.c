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

/* 
Ejercicio 1.
Crea una Lista y agrega punteros a elementos del 1 al 10.
Recuerda que la lista almacena punteros, por lo que
debes reservar memoria para cada elemento que agregues.
Al finalizar retorna la lista creada.
*/

#include "arraylist.h"
#include <stdlib.h>

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

/*
Ejercicio 2.
Crea una función que reciba una lista de enteros (int*) y 
retorne la suma de sus elementos.
*/
int sumaLista(List *L) {
    int sum = 0;
    for (void* data = first(L); data != NULL; data = next(L)) {
        sum += *(int*)data;
    }
    return sum;
}
/*
Ejercicio 3.
Crea una función que reciba una lista de punteros a int (int*) y
un entero elem. La función debe eliminar todos los elementos 
de la lista que sean iguales a elem.
Asume que popCurrent luego de eliminar un elemento se
posiciona en el elemento anterior.
*/

void eliminaElementos(List *L, int elem) {
    for (void* data = first(L); data != NULL; data = next(L)) {
        if (*(int*)data == elem) {
            popCurrent(L);
        }
    }
}

/*
Ejercicio 4.
La función copia los punteros de la pila P1 en la pila P2.
El orden de ambas pilas se debe mantener.
Puedes usar una pila auxiliar.
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

/*
Ejercicio 5.
La función verifica si la cadena de entrada tiene sus 
paraéntesis balanceados. Retorna 1 si están balanceados,
0 en caso contrario.
*/

#include <stdlib.h>
#include <string.h>

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
