#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// #include "cliente.h"
// #include "carro.h"
#include "geral.h"


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
    char op1[3];

    printf("1 - CLIENTE\n");
    printf("2 - VEICULO\n");
    printf("3 - SAIR\n");

    printf("Escolha uma opcao: ");
    
    return teste_input(op1);
}

int menu_cliente(void){
    system(clear());
    char op2[3];

    printf("1 - ALUGAR\n"); // submenu: adicionar cliente            
    printf("2 - LISTAR\n"); // submenu: historico do cliente
    printf("3 - BUSCAR\n"); // submenu: editar cliente e historico
    printf("4 - CONSULTAR QUANTIDADE\n");    
    printf("5 - REMOVER CLIENTE\n");    
    printf("6 - VOLTAR\n");    
    
    printf("Escolha uma opcao: ");

    return teste_input(op2);
}

int menu_carro(void){
    system(clear());
    char op3[3];

    printf("1 - ADICIONAR\n"); 
    printf("2 - LISTAR\n"); //submenu: consultar disp. e consultar historico
    printf("3 - CONSULTAR CARROS\n");
    printf("4 - VOLTAR\n");

    printf("Escolha uma opcao: ");
    
    return teste_input(op3); 
}

int compara(char *nome, char *nome_busca){
    /* Função que faz a comparação entre o nome e o nome 
       da busca a partir do seu tamanho
    */
    return strncmp(nome, nome_busca, strlen(nome_busca)); 
}

int teste_formato(char *num){
    
}

int teste_input(char *resp) // editar função
{
    scanf(" %2[^\n]", resp);
    fflush(stdin);
    int len = strlen(resp);
    if(len == 1) {
        return toupper(resp[0]);
    } else if(len >= 2) {
        //printf(TXT_red"\nLimite de caracter atingido!"TXT_reset);
    }
    return 0;
}