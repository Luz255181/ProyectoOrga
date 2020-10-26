#include <stdio.h>
#include <stdlib.h>

#include "mapeo.h"

void reHash(tMapeo m);

void crear_mapeo(tMapeo *m, int ci, int (*fHash)(void *), int (*fComparacion)(void *, void *))
{
    *m = (tMapeo)malloc(sizeof(struct mapeo));
    int i,longitud;
    if (*m == NULL)
    {
        exit(MAP_ERROR_MEMORIA);
    }
    longitud = 10 > ci ? 10 : ci;
    (*m)->longitud_tabla = longitud;
    (*m)->cantidad_elementos = 0;
    (*m)->comparador = fComparacion;
    (*m)->hash_code = fHash;
    (*m)->tabla_hash = (tLista *)malloc(longitud*sizeof(struct celda));
    for(i = 0; i<longitud;i++){
        crear_lista(((*m)->tabla_hash)+i);
    }
}

tValor m_insertar(tMapeo m, tClave c, tValor v)
{
    tValor vi = NULL;
    tEntrada cursor,nuevo;
    tLista bucket;
    int i;
    int encontre = 0;
    int hash = (m->hash_code(c))%(m->longitud_tabla);
    bucket = *((m->tabla_hash)+hash);
    tPosicion pos = l_primera(bucket);
    for(i = 0; !encontre && i<l_longitud(bucket); i++)
    {
        cursor = (tEntrada)l_recuperar(bucket,pos);
        if(m->comparador(c,cursor->clave))
        {
            encontre = !encontre;
            vi = cursor->valor;
            cursor ->valor = v;
        }
        else
        {
            if(l_fin(bucket) != pos)
                pos = l_siguiente(bucket,pos);
        }
    }
    if(!encontre)
    {
        nuevo = (tEntrada)malloc(sizeof(struct entrada));
        if(nuevo == NULL)
        {
            exit(MAP_ERROR_MEMORIA);
        }
        nuevo->clave = c;
        nuevo->valor = v;
        l_insertar(bucket,l_primera(bucket),nuevo);
        (m->cantidad_elementos)++;
    }
    if((m->cantidad_elementos)> (m->longitud_tabla)*0.75)
    {
        reHash(m);
    }
    return vi;
}

void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *))
{
    int encontre = 0,i;
    tEntrada cursor;
    tLista bucket;
    int hash = (m->hash_code(c))%(m->longitud_tabla);
    bucket = *((m->tabla_hash)+hash);
    tPosicion pos = l_primera(bucket);
    for(i = 0; !encontre && i<l_longitud(bucket); i++)
    {
        cursor = (tEntrada)l_recuperar(bucket,pos);
        if(m->comparador(c,cursor->clave))
        {
            encontre = !encontre;
            fEliminarV(cursor->valor);
            fEliminarC(cursor->clave);
            (m->cantidad_elementos)--;
            l_eliminar(bucket,pos,&free());
        }
        else
        {
            if(l_fin(bucket) != pos)
                pos = l_siguiente(bucket,pos);
        }
    }
}

void m_destruir(tMapeo *m, void (*fEliminarC)(void *), void (*fEliminarV)(void *))
{
    tEntrada cursor;
    tLista bucket;
    int i,j;
    tPosicion pos;
    for(i = 0; i<((*m)->longitud_tabla); i++)
    {
        bucket = *(((*m)->tabla_hash)+i);
        while(l_longitud != 0)
        {
            pos = l_primera(bucket);
            cursor = l_recuperar(bucket,pos);
            fEliminarC(cursor->clave);
            fEliminarV(cursor->valor);
            l_eliminar(bucket,pos,&free());
        }
        l_destruir(bucket,&free())
    }
    free(((*m)->tabla_hash));
    free(*m);
}

/**
 Recupera el valor correspondiente a la entrada con clave C en M, si esta existe.
 Retorna el valor correspondiente, o NULL en caso contrario.
**/
extern tValor m_recuperar(tMapeo m, tClave c)
{
    int encontre = 0,i;
    tValor v = NULL;
    tEntrada cursor;
    tLista bucket;
    int hash = (m->hash_code(c))%(m->longitud_tabla);
    bucket = *((m->tabla_hash)+hash);
    tPosicion pos = l_primera(bucket)
    for(i = 0; !encontre && i<l_longitud(bucket); i++)
    {
        cursor = (tEntrada)l_recuperar(bucket,pos);
        if(m->comparador(c,cursor->clave))
        {
            encontre = !encontre;
            v = cursor->valor;
        }
        else
        {
            if(l_fin(bucket) != pos)
                pos = l_siguiente(bucket,pos);
        }
    }
    return v;
}
