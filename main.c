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
void realoca_string(char* str);


int main(void) {

    Cliente *clientes = NULL;
    int op;
    do {
        op = menu_principal();
        switch (op) {
        case '1':
            menu_cliente();
            break;
        
        case '2':
            menu_carro();
            break;

        case '3':
            printf("Encerrando programa...");
            break;

        default:    
            printf("Insira uma opcao valida!");
            break;
        }
    } while (op != '3');
    
    // clientes = cliente_cadastra(clientes, "gustavo", "01231212323", "88912345678");
    // clientes = cliente_cadastra(clientes, "antonio", "16537654525", "88909090909");
    // clientes = cliente_cadastra(clientes, "Bernardo", "16147634120", "88914253657");
    
    // clientes = cliente_exclui(clientes, "01231212323");
    
    // // int nada;
    // // nada = opcao_cliente();
    // cliente_libera(clientes);
    printf("\ntchau");

    return 0;
}


// void realoca_string(char* str)
// {
//    realloc(str, strlen(str)*sizeof(char));
// }