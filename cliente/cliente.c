#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../carro/carro.c"
#include "cliente.h"

struct cliente
{
   char *nome;
   char data_aluguel;
   char duracao;
   char *documento;
   char *telefone;
   Carro *carro;
   Cliente *prox_cliente;
   FILE* file;
};

Cliente *cliente_cadastra(Cliente* cli, char *nome, char *documento, char *telefone)
{
   // cria um cliente:
   Cliente *cliente = (Cliente*)malloc(sizeof(Cliente));
   if (cliente == NULL) exit(1);

   // cadastra os dados do cliente:
   strcpy(cliente->nome, nome);
   strcpy(cliente->documento, documento);
   Carro *carro = carro_aluga(void, void);

   // encadea o endereço do cliente anterior ao próximo:
   cliente->prox_cliente = cli;

}

Cliente *cliente_exclui()
{

}

Cliente *cliente_busca(Cliente *cli, char* dado_busca, int tipo)
{
   Cliente *C;
   if (tipo == 0)
   {
      for (C = cli; C != NULL; C = C->prox_cliente)
      {
         if (strcmp(C->nome, dado_busca) == 0)
            return C;
      }
      return NULL;
   }
   else 
   {
      for (C = cli; C != NULL; C = C->prox_cliente)
      {
         if (strcmp(C->nome, dado_busca) == 0)
            return C;
      }
      return NULL;
   }
}

void cliente_edita()
{

}

int cliente_total()
{

}