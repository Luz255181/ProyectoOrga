#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "mapeo.h"

// Macros con c�digos de finalizaci�n
#define SUCCESS                     0
#define EV_ERROR_ARCHIVO           -1
#define EV_ERROR_INVOCACION        -2

//declaración de funciones
void contador(tMapeo map, FILE* file);
int fComparacion(void *cadena1, void* cadena2);
int fHash(void* string);
void fEliminarC(void* c);
void fEliminarV(void* v);

int main(int argc, char const *argv[])
{
    //declaracion de variables
    char *ruta,*aBuscar;
    int opcion,*cant;
    FILE * fp;
    tMapeo map;
    cant = malloc(sizeof(int));
    ruta = malloc(sizeof(char)*50);
    aBuscar = malloc(sizeof(char)*50);

    //control de memoria
    if(cant == NULL || ruta == NULL || aBuscar == NULL)
    {
        printf("Error de memoria");
        exit(EV_ERROR_INVOCACION);
    }

    //control de parametros
    if(argc == 2){
        //inicializar el archivo, el mapeo y el contador de palabras
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

    //menu de opciones
    while (1){

        printf("**************************************************** \n Opciones: \n");
        printf("1. Cantidad de apariciones de una palabra.\n");
        printf("2. Salir.\n");
        printf("Ingrese la opcion elegida: ");
        scanf("%d",&opcion);
        printf("\n");
        fflush(stdin);//Limpia el buffer
        if (opcion==1)
        {
            printf("ingrese la palabra a buscar:\n");
            scanf("%49[^\n]",aBuscar);
            fflush(stdin);
            cant = (int*) m_recuperar(map,aBuscar);
            if(cant!=NULL)
                printf("la cantidad de veces que aparece \" %s \" en el archivo es %d.\n\n",aBuscar,*cant);
            else{
                printf("La palabra no se encontro.\n");
            }
        }
        else if (opcion==2)
        {
            //libero memoria y finalizo con valor 0
            printf("Gracias por usar la aplicacion:\n");
            free(cant);
            free(aBuscar);
            free(ruta);
            m_destruir(&map,&fEliminarC,&fEliminarV);
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

/**
* Recorre el archivo e introduce cada palabra en el mapeo,
* Si la palabra ya ese encuentra en el mapeo incrementa su valor en 1.
* En caso contrario ingresa la nueva palabra en el mapeo con valor 1.
*/
void contador(tMapeo map,FILE *file)
{
    char *palabra ;
    int* valor;
    while(!feof(file))
    {
        palabra=malloc(sizeof(char)*50);//reservo memoria para la palabra de max 49 char
        if(palabra == NULL)
        {
            printf("Error de memoria");
            exit(EV_ERROR_INVOCACION);
        }
        fscanf(file,"%s",palabra);
        valor = m_recuperar(map, palabra);
        if(valor == NULL)//no se encuentra en el mapeo
        {
            valor = malloc(sizeof(int));
            if(valor == NULL)
            {
                printf("Error de memoria");
                exit(EV_ERROR_INVOCACION);
            }
            *valor = 1;
            m_insertar(map,palabra,valor);
        }
        else//ya se encontraba en el mapeo
        {
            *valor=*valor+1;
            //libero memoria de palabra no usada
            free(palabra);
        }
    }
}

/**
* Calcula el valor de hash de cada cadena de caracteres sumando los valores ascii de cada caracter.
*/
int fHash(void* string)
{
    char* str=(char*) string;
    int hash = 0,i=1;
    char puntero= *str;
    while(puntero != '\0'){
        hash+=(int) puntero;
        puntero= *(str + i);
        i++;
    }
    return hash;
}

/**
* Compara 2 cadena de caracteres
* retorna true en caso de ser iguales y false en caso contrario.
*/
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

/**
*  Libera el espacio de memoria de la cadena de caracteres
*/
void fEliminarC(void* c){
    free(c);
}

/**
*  Libera el espacio de memoria del entero.
*/
void fEliminarV(void * v){
    int *a=(int* )v;
    *a=0;
    free(a);
}
