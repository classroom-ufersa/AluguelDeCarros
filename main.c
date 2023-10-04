#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "./carro/carro.c"
#include "./cliente/cliente.c"
#include "./geral/geral.c"
// #include "carro.h" // pensei em nao ser possivel modificar nada do carro, ento so o cliente.c ja seria suficiente 
// #include "cliente.c"

char *clear(void);
int opcao_cliente(void);
int opcao_carro(void);
// void realoca_string(char* str);


int main(void) {

    Cliente *clientes = NULL;
    Carro *carros = NULL;
    int op1 = 0, op2 = 0, op3 = 0;
    
    /* Recuperando dados salvos */
    printf("Carregando dados dos Clientes...\n");
    if((clientes = cliente_leia(clientes, carros)) != NULL)
        printf("Dados recuperados com sucesso\n");

    // delay(1000);     /* atraso para verificar resposta */

    // Menu principal:
    do {
        op1 = menu_principal();
        switch (op1) {
            case '1':
                printf("\nAbrindo Menu dos Clientes...\n");
                delay(500);
                clientes = menu_cliente(clientes);
                break;
            
            case '2':
                printf("\nAbrindo Menu dos Carros...\n");
                delay(500);
                carros = menu_carro(carros);
                break;

            case '3':
                printf("\nEncerrando programa...\n");
                delay(500);
                if (clientes != NULL) {
                    cliente_registra(clientes);
                }

                break;

            default:    
                printf("\nInsira uma opcao valida!\n");
                break;
        }
    } while (op1 != '3');
    

    // clientes = cliente_cadastra(clientes, "gustavo", "01231212323", "88912345678");
    // clientes = cliente_cadastra(clientes, "antonio", "16537654525", "88909090909");
    // clientes = cliente_cadastra(clientes, "Bernardo", "16147634120", "88914253657");
    
    // clientes = cliente_exclui(clientes, "01231212323");
    
    // // int nada;
    // // nada = opcao_cliente();
    cliente_libera(clientes);
    // carro_libera(carros);
    printf("\ntchau");

    return 0;
}


// void realoca_string(char* str)
// {
//    realloc(str, strlen(str)*sizeof(char));
// }