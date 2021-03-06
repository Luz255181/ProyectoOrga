#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
void crear_lista(tLista *l)
{
    *l = (tLista)malloc(sizeof(struct celda));
    if (*l == NULL)
        exit(LST_ERROR_MEMORIA);
    (*l)->elemento = NULL;
    (*l)->siguiente = NULL;
}

void l_insertar(tLista l, tPosicion p, tElemento e)
{
    if (p == NULL)
    {
        exit(LST_POSICION_INVALIDA);
    }
    tPosicion nueva = (tPosicion)malloc(sizeof(struct celda));
    if (nueva == NULL)
        exit(LST_ERROR_MEMORIA);
    nueva->elemento = e;
    nueva->siguiente = p->siguiente;
    p->siguiente = nueva;
}

void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento))
{
    if (p->siguiente == NULL) //p es fin(L)
    {
        printf("error en eliminar lista");
        exit(LST_POSICION_INVALIDA);
    }
    tPosicion elim = p->siguiente;
    p->siguiente = elim->siguiente;
    tElemento e = elim->elemento;
    fEliminar(e);
    free(elim);
}

void l_destruir(tLista *l, void (*fEliminar)(tElemento))
{
    while ((*l)->siguiente != NULL)
        l_eliminar(*l, *l, fEliminar);
    free(*l);
    *l=NULL;
}

tElemento l_recuperar(tLista l, tPosicion p)
{
    if (p->siguiente == NULL) //p es fin(L)
    {
        exit(LST_POSICION_INVALIDA);
    }
    return (p->siguiente)->elemento;
}

tPosicion l_primera(tLista l)
{
    return l;
}

tPosicion l_siguiente(tLista l, tPosicion p)
{
    if (p->siguiente == NULL)
        exit(LST_NO_EXISTE_SIGUIENTE);
    return p->siguiente;
}

tPosicion l_anterior(tLista l, tPosicion p)
{
    if (p == l)
        exit(LST_NO_EXISTE_ANTERIOR);
    tPosicion cursor = l;
    while (cursor->siguiente != p)
        cursor = cursor->siguiente;
    return cursor;
}

tPosicion l_ultima(tLista l)
{
    tPosicion cursor = l;
    if (cursor->siguiente==NULL)
        return cursor;
    while (cursor->siguiente->siguiente != NULL)
        cursor = cursor->siguiente;
    return cursor;
}

tPosicion l_fin(tLista l)
{
    tPosicion cursor = l;
    while (cursor->siguiente != NULL)
        cursor = cursor->siguiente;
    return cursor;
}

int l_longitud(tLista l)
{
    int i=0;
    tPosicion cursor=l;
    while(cursor->siguiente!=NULL){
        i++;
        cursor=cursor->siguiente;
    }
    return i;
}
