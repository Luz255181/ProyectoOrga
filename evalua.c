#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mapeo.h"

// Macros con c�digos de finalizaci�n
#define SUCCESS                     0 
#define EV_ERROR_ARCHIVO           -1
#define EV_ERROR_INVOCACION        -2

int comprobar_ruta(char* ruta);

int main(int argc, char const *argv[])
{
    char* ruta,*aBuscar;
    int opcion,*cant;
    cant=(int*) malloc(sizeof(int));
    aBuscar =(char*) malloc(sizeof(char)*50);
    tMapeo map;

    if(argc == 2){
        ruta=strcpy(ruta,argv[1]);
    }else{
        printf("Error al invocar el programa.\n");
        exit(EV_ERROR_INVOCACION);
    }
    
    if(!comprobar_ruta(ruta)){
        printf("Error al encontrar el archivo.\n");
        exit(EV_ERROR_ARCHIVO);
    }

    while (1){
        printf("Ingrese una opcion: \n");
        scanf("%d",&opcion);
        if (opcion==1)
        {
            printf("ingrese la palabra a buscar:\n");
            scanf("%s",aBuscar);
            cant = (int*) m_recuperar(map,aBuscar);
            printf("la cantidad de veces que aparece \" %s \" en el archivo es %d.\n",aBuscar,*cant);
        }
        else if (opcion==2)
        {
            printf("Gracias por usar la aplicacion:\n");
            free(cant);
            free(aBuscar);
            //otros free y destroy;
            exit(SUCCESS);
        }
        else
        {
            printf("Opcion erronea.\n");
        }
        
    }
    
    return 0;
}
