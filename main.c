#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "carro.h" // pensei em nao ser possivel modificar nada do carro, ento so o cliente.c ja seria suficiente 
// #include "cliente.c"

char *clear(void);
int opcao_cliente(void);
int opcao_carro(void);
void realoca_string(char* str);



int main(void) {

    int nada;
    nada = opcao_cliente();
    printf("%d", nada);

    return 0;
}

char *clear(void){
    // Checking for windows OS with
    // _WIN32 macro
    #ifdef _WIN32
        return "cls";

    // Checking for mac OS with
    // __APPLE__ macro
    #elif __APPLE__
        return "cls";

    // Checking for linux OS with
    // __linux__ macro
    #elif __linux__
        return "clear";
    #endif
}

int opcao_cliente(void){
    system(clear());
    int opcao;
    /*\t\t\t\t\t\t\t\t*/
    /*\t\t\t\t\t\t\t\t*/
    /*\t\t\t\t\t\t\t\t*/
    /*\t\t\t\t\t\t\t\t*/
    /*\t\t\t\t\t\t\t\t*/
    /*\t\t\t\t\t\t\t\t*/
    printf("1 - ADICIONAR CLIENTE\n");                 
    printf("2 - ALUGAR CARRO\n");   
    printf("3 - LISTAR CLIENTE\n");    
    printf("4 - BUSCAR CLIENTE\n");    
    printf("5 - EDITAR CLIENTE\n");    
    printf("6 - CONSULTAR LISTA DE CLIENTE\n");    
    
    scanf("%d", &opcao);

    return opcao;
}

void realoca_string(char* str)
{
   realloc(str, strlen(str)*sizeof(char));
}