#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "carro.h"
#include "geral.h"

/*
Menu inicial: 
1. cliente
2. veículo
3. sair

menu cliente: 
Aluga: add; Listar: historico; Buscar: editar, historico;
Consultar qtde; Remover cliente; Voltar.

menu carro: 
Add; Listar: consultar disp., consultar hist.; Consulta carro; 
Voltar.
*/

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

int menu_principal(void){
    system(clear());
    int op1;

    printf("1 - CLIENTE\n");
    printf("2 - VEICULO\n");
    printf("3 - SAIR\n");

    scanf("%d", &op1);
    
    return op1;
}

int menu_cliente(void){
    system(clear());
    int op2;

    printf("1 - ALUGAR\n"); // submenu: adicionar cliente            
    printf("2 - LISTAR\n"); // submenu: historico do cliente
    printf("3 - BUSCAR\n"); // submenu: editar cliente e historico
    printf("4 - CONSULTAR QUANTIDADE\n");    
    printf("5 - REMOVER CLIENTE\n");    
    printf("6 - VOLTAR\n");    
    
    scanf("%d", &op2);

    return op2;
}

int menu_carro(void){
    system(clear());
    int op3;

    printf("1 - ADICIONAR\n"); 
    printf("2 - LISTAR\n"); //submenu: 
    printf("3 - CONSULTAR CARROS\n");
    prinft("4 - VOLTAR\n");

    scanf("%d", &op3);

    return op3;
}