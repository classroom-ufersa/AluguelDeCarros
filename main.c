#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./carro/carro.c"
#include "./cliente/cliente.c"
// #include "carro.h" // pensei em nao ser possivel modificar nada do carro, ento so o cliente.c ja seria suficiente 
// #include "cliente.c"

char *clear(void);
int opcao_cliente(void);
int opcao_carro(void);
void realoca_string(char* str);



int main(void) {

    Cliente *clientes = NULL;
    clientes = cliente_cadastra(clientes, "gustavo", "01231212323", "88912345678");
    
    
    // int nada;
    // nada = opcao_cliente();
    cliente_libera(clientes);
    printf("\ntchau");

    return 0;
}


// void realoca_string(char* str)
// {
//    realloc(str, strlen(str)*sizeof(char));
// }