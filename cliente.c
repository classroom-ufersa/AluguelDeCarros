#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include <string.h>
#include "carro.c"

struct cliente
{
   char *nome[80];
   long long int data_alugel; // pode ser feito com string
   int duracao; // pensei em fazer em dias
   char *documento[13];
   Carro *carro;
};

Cliente *cria_cliente(char *nome, char *documento, long long int data_aluguel, int duracao){
   Cliente *cliente = (Cliente*) malloC(sizeof(Cliente));
   if(cliente == NULL){exit(1);}

   strcpy(cliente->nome, nome);
   strcpy(cliente->documento, documento);

   Carro *carro = aluga_carro(void);

}