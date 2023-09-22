#include "cliente.h"
#include "carro.c"

struct cliente
{
   char *nome[80];
   long long int data_alugel; // pode ser feito com string
   int duracao; // pensei em fazer em dias
   char *documento[13];
   Carro *carro;
};
