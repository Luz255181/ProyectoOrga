#include "mapeo.h"
#include <stdio.h>
#include <stdlib.h>

void contador(tMapeo map,int (*fHash)(void *), int (*fComparacion)(void *, void *)){
    FILE * fp;
    fp = fopen("test.txt","r");
    char * palabra = malloc(sizeof(char)*50);
    int * valor;
    int * valor_recuperado = malloc(sizeof(int));

    char * cadena = malloc(sizeof(char)*50);
    cadena = "mucho";

    while(!feof(fp)){
        fscanf(fp,"%s",palabra);
        valor = m_recuperar(map, palabra);
        if(valor == NULL){
            valor=malloc(sizeof(int));
            *valor=1;
            m_insertar(map,palabra,valor);
        }else{
            *valor=(*valor)+1;
        }
    }
   valor_recuperado = m_recuperar(map, cadena);

  //  free(valor);
   // free(palabra);
   // valor_recuperado = m_recuperar(map,palabra);
    printf("valor de la palabra:  %i \n",*valor_recuperado );
   // printf("tamaño del mapeo:  %i \n",map->cantidad_elementos);
}

