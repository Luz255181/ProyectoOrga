#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "mapeo.h"

int comparador(void* caracter1, void* caracter2);
int fHash(void* caracter);
void fEliminarC(void* clave);
void fEliminarV (void* valor);

int main()
{
    tMapeo m=NULL;
    void* prueba;
    char* c,*c2, *c3;
    int* v,*v2;
    int ci;
    ci = 5;
    c = (char*) malloc(sizeof(char));
    v = (int*)malloc(sizeof(int));
    c2 = (char*)malloc(sizeof(char));
    v2 = (int*)malloc(sizeof(int));
    c3 = (char*)malloc(sizeof(char));
    *c = 'd';
    printf("el valor del puntero c: %p, es : %c\n",c, *c);
    *v = 6;
    printf("el valor del puntero v: %p, es : %d\n",v, *v);
    *c2 = 'd';
    printf("el valor del puntero c2: %p, es : %c\n",c2, *c2);
    *v2 = 4;
    printf("el valor del puntero v2: %p, es : %d\n",v2, *v2);
    *c3 = 'h';
    printf("el valor del puntero c3: %p, es : %c\n",c3, *c3);
    crear_mapeo(&m,ci, &fHash,&comparador);
    prueba = m_insertar(m,c,v);
    printf("el puntero que devuelve insertar con clave c y valor v es:%p\n",prueba);
    prueba = m_insertar(m,c2,v2);
    printf("el puntero que devuelve insertar con clave c2 y valor v2 es:%p\n",prueba);
    prueba = m_recuperar(m,c);
    printf("el puntero que devuelve recuperar con clave c es:%p\n",prueba);
    prueba = m_recuperar(m,c2);
    printf("el puntero que devuelve recuperar con clave c2 es:%p\n",prueba);
    m_eliminar(m,c3,&fEliminarC,&fEliminarV);
    prueba = m_recuperar(m,c3);
    printf("el puntero que devuelve recuperar con clave c3 es:%p\n",prueba);
    m_eliminar(m,c2,&fEliminarC,&fEliminarV);
    prueba = m_recuperar(m,c2);
    printf("el puntero que devuelve recuperar con clave c2 es:%p\n",prueba);
    m_destruir(&m,&fEliminarC,&fEliminarV);
    free(c);
    free(c2);
    free(v);
    free(v2);
    free(c3);
    return 0;
}

int comparador(void*caracter1, void* caracter2)
{
    char* a = (char*) caracter1;
    char* b = (char*) caracter2;
    return (*a == *b);
}

int fHash(void* caracter)
{
    char *a=(char*) caracter;
    return (*a);
}

void fEliminarC(void* clave)
{
    free(clave);
}
void fEliminarV(void* valor)
{
    free(valor);
}
