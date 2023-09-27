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


void realoca_string(char* str)
{
   realloc(str, strlen(str)*sizeof(char));
}