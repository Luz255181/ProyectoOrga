#include <stdio.h>
#include <stdlib.h>

#include "mapeo.h"

void reHash(tMapeo m);
void fEliminarEntrada(void *entrada);
void (*eliminarClave)(void *);
void (*eliminarValor)(void *);

void crear_mapeo(tMapeo *m, int ci, int (*fHash)(void *), int (*fComparacion)(void *, void *))
{
    *m = (tMapeo)malloc(sizeof(struct mapeo));
    int i, longitud;
    if (*m == NULL)
    {
        exit(MAP_ERROR_MEMORIA);
    }
    longitud = 10 > ci ? 10 : ci;
    (*m)->longitud_tabla = longitud;
    (*m)->cantidad_elementos = 0;
    (*m)->comparador = fComparacion;
    (*m)->hash_code = fHash;
    (*m)->tabla_hash = (tLista *)malloc(longitud * sizeof(tLista));
    if ((*m)->tabla_hash == NULL)
    {
        exit(MAP_ERROR_MEMORIA);
    }
    for (i = 0; i < longitud; i++)
    {
        crear_lista(((*m)->tabla_hash) + i);
    }
}

tValor m_insertar(tMapeo m, tClave c, tValor v)
{
    tValor vi = NULL;
    tEntrada cursor, nuevo;
    tLista bucket;
    tPosicion pos;
    int i, longitud;
    int encontre = 0;
    int hash = (m->hash_code(c)) % (m->longitud_tabla);
    bucket = *((m->tabla_hash) + hash);
    longitud = l_longitud(bucket);
    for (i = 0; !encontre && i < longitud; i++)
    {
        pos = l_primera(bucket);
        cursor = (tEntrada)l_recuperar(bucket, pos);
        if (m->comparador(c, cursor->clave))
        {
            encontre = !encontre;
            vi = cursor->valor;
            cursor->valor = v;
        }
        else
        {
            if (l_fin(bucket) != pos)
                pos = l_siguiente(bucket, pos);
        }
    }
    if (!encontre)
    {
        nuevo = (tEntrada)malloc(sizeof(struct entrada));
        if (nuevo == NULL)
        {
            exit(MAP_ERROR_MEMORIA);
        }
        nuevo->clave = c;
        nuevo->valor = v;
        l_insertar(bucket, l_primera(bucket), nuevo);
        (m->cantidad_elementos)++;
    }
    if ((m->cantidad_elementos) > (m->longitud_tabla) * 0.75)
    {
        reHash(m);
    }
    return vi;
}

void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *))
{
    int encontre = 0, i, longitud;
    tEntrada cursor;
    tLista bucket;
    tPosicion pos;
    int hash = (m->hash_code(c)) % (m->longitud_tabla);
    eliminarClave = fEliminarC;
    eliminarValor = fEliminarV;
    bucket = *((m->tabla_hash) + hash);
    longitud = l_longitud(bucket);
    for (i = 0; !encontre && i < longitud; i++)
    {
        pos = l_primera(bucket);
        cursor = (tEntrada)l_recuperar(bucket, pos);
        if (m->comparador(c, cursor->clave))
        {
            encontre = !encontre;
            fEliminarV(cursor->valor);
            fEliminarC(cursor->clave);
            (m->cantidad_elementos)--;
            l_eliminar(bucket, pos, &fEliminarEntrada);
        }
        else
        {
            if (l_fin(bucket) != pos)
                pos = l_siguiente(bucket, pos);
        }
    }
}

void m_destruir(tMapeo *m, void (*fEliminarC)(void *), void (*fEliminarV)(void *))
{
    tEntrada cursor;
    tLista bucket;
    int i, longitud;
    tPosicion pos;
    eliminarClave = fEliminarC;
    eliminarValor = fEliminarV;
    for (i = 0; i < ((*m)->longitud_tabla); i++)
    {
        bucket = *(((*m)->tabla_hash) + i);
        longitud = l_longitud(bucket);
        while (longitud)
        {
            pos = l_primera(bucket);
            cursor = l_recuperar(bucket, pos);
            fEliminarC(cursor->clave);
            fEliminarV(cursor->valor);
            l_eliminar(bucket, pos, &fEliminarEntrada);
        }
        l_destruir(&bucket, &fEliminarEntrada);
    }
    free(((*m)->tabla_hash));
    free(*m);
    *m = NULL;
}

tValor m_recuperar(tMapeo m, tClave c)
{
    int encontre = 0, i, l_long;
    tValor v = NULL;
    tEntrada cursor;
    tLista bucket;
    tPosicion pos;
    int hash = (m->hash_code(c)) % (m->longitud_tabla);
    bucket = *((m->tabla_hash) + hash);
    l_long = l_longitud(bucket);
    if (l_long > 0)
    {
        pos = l_primera(bucket);
        for (i = 0; !encontre && i < l_long; i++)
        {
            cursor = (tEntrada)l_recuperar(bucket, pos);
            if (m->comparador(c, (cursor->clave)))
            {
                encontre = !encontre;
                v = cursor->valor;
            }
            else
            {
                pos = l_siguiente(bucket, pos);
            }
        }
    }

    return v;
}

void noEliminar(void *elem) {}

void reHash(tMapeo m)
{
    tLista *nuevo_hash;
    tLista bucket;
    int i, nuevaLong, hash,l_long;
    tPosicion pos;
    tEntrada cursor;
    nuevaLong = (m->longitud_tabla) * 2;
    nuevo_hash = (tLista *)malloc(nuevaLong * sizeof(tLista));
    for (i = 0; i < nuevaLong; i++)
    {
        crear_lista(nuevo_hash + i);
    }
    for (i = 0; i < (m->longitud_tabla); i++)
    {
        bucket = *((m->tabla_hash) + i);
        l_long = l_longitud(bucket);
        while (l_long != 0)
        {
            pos = l_primera(bucket);
            cursor = l_recuperar(bucket, pos);
            hash = (m->hash_code(cursor->clave)) % (nuevaLong);
            l_insertar((*(nuevo_hash + hash)), l_primera(*(nuevo_hash + hash)), cursor);
            l_eliminar(bucket, pos, &noEliminar);
        }
        l_destruir(&bucket, &noEliminar);
    }
    free(m->tabla_hash);
    m->tabla_hash = nuevo_hash;
}

void fEliminarEntrada(void *entrada)
{
    tEntrada ent = (tEntrada)entrada;
    eliminarClave(ent->clave);
    eliminarValor(ent->valor);
    free(ent);
}

