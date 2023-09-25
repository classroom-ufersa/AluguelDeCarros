#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "carro.h"

struct cliente
{
   char *nome;
   long long int data_aluguel; // pode ser feito com string
   int duracao; // pensei em fazer em dias
   char *documento;
   Carro *carro;
   Cliente *prox_cliente;
};

Cliente *cliente_cadastra(Cliente* cli, char *nome, char *documento, long long int data, int duracao)
{
   // cria um cliente:
   Cliente *cliente = (Cliente*)malloc(sizeof(Cliente));
   if (cliente == NULL) exit(1);

   // cadastra os dados do cliente:
   strcpy(cliente->nome, nome);
   cliente->data_aluguel= data;
   cliente->duracao = duracao;
   strcpy(cliente->documento, documento);
   Carro *carro = carro_aluga();

   // encadea o endereço do cliente anterior ao próximo:
   cliente->prox_cliente = cli;

}

Cliente *cliente_exclui()
{

}

Cliente *cliente_busca()
{

}

void cliente_edita()
{

}

int cliente_total()
{

}