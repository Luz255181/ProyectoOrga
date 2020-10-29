#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "mapeo.h"

// Macros con c�digos de finalizaci�n
#define SUCCESS                     0
#define EV_ERROR_ARCHIVO           -1
#define EV_ERROR_INVOCACION        -2

void contador(tMapeo map, FILE* file);
int fComparacion(void *cadena1, void* cadena2);
int fHash(void* string);

void imprimir_clave(void* c){
    char * s = (char *) c;
    printf("%s\n",s);
}

int main(int argc, char const *argv[])
{
    char *ruta,*aBuscar;
    int opcion,*cant;
    FILE * fp;
    cant = malloc(sizeof(int));
    ruta = malloc(sizeof(char)*50);
    aBuscar = malloc(sizeof(char)*50);
    tMapeo map;

    if(argc == 2){
        strcpy(ruta,argv[1]);
        fp = fopen(ruta,"r");
        if(fp==NULL){
            printf("Error al encontrar el archivo.\n");
            exit(EV_ERROR_ARCHIVO);
        }
        crear_mapeo(&map,50,&fHash,&fComparacion);
        contador(map,fp);
    }else{
        printf("Error al invocar el programa.\n");
        exit(EV_ERROR_INVOCACION);
    }

    while (1){
        printf("Ingrese una opcion: \n");
        printf("1. Cantidad de apariciones de una palabra.\n");
        printf("2. Salir.\n");
        scanf("%d",&opcion);
        fflush(stdin);
        if (opcion==1)
        {
            printf("ingrese la palabra a buscar:\n");
            scanf("%49[^\n]",aBuscar);
            fflush(stdin);
            cant = (int*) m_recuperar(map,aBuscar);
            if(cant!=NULL)
                printf("la cantidad de veces que aparece \" %s \" en el archivo es %d.\n",aBuscar,*cant);
            else{
                printf("La palabra no se encontro.\n");
            }
        }
        else if (opcion==2)
        {
            printf("Gracias por usar la aplicacion:\n");
            free(cant);
            free(aBuscar);
            //otros free y destroy;
            fclose(fp);
            exit(SUCCESS);
        }
        else
        {
            printf("Opcion erronea.\n");
        }
    }

    return 0;
}

void contador(tMapeo map,FILE *file){
    char *palabra ;
    int* valor;
    while(!feof(file)){
        palabra=malloc(sizeof(char)*50);
        fscanf(file,"%s",palabra);
        if(strcmp(palabra,"")>0){
            valor = m_recuperar(map, palabra);
            if(valor == NULL){
                valor = malloc(sizeof(int));
                *valor = 1;
                m_insertar(map,palabra,valor);
            }else{
                *valor=*valor+1;
            }
            valor = m_recuperar(map, palabra);
        }
    }
}

int fHash(void* string)
{
    char* str=(char*) string;
    int hash = 24,i=1;
    char puntero= *str;
    while(puntero != '\0'){
        hash+=(int) puntero;
        puntero= *(str + i);
        i++;
    }
    return hash;
}
int fComparacion(void *cadena1, void* cadena2)
{
    char * a = (char*) cadena1;
    char * b = (char*) cadena2;
    int toret=0;
    if(a!=NULL && b!=NULL){
        toret = !(strcmp(a,b));
    }
    return toret;
}
