#include <stdio.h>
#include <stdlib.h>
#include "../carro/carro.c"
#include "aluguel.h"
// #include "../cliente/cliente.h"

struct aluguel
{
    char *data_aluguel;
    int duracao;
    int status;     /* 1 -> alugando carro, 0 -> não está alugando */
    
    Carro *carro;
    Aluguel *prox_aluguel;
};

Aluguel *aluguel_inicializa(Aluguel* aluguel)
{
    Aluguel *novo_aluguel = (Aluguel*)malloc(sizeof(Aluguel));
    if (novo_aluguel == NULL)
    {
        printf("\nNao foi possivel criar o registro de aluguel\n");
        return NULL;
    }

    novo_aluguel->status = 0;
    aluguel = novo_aluguel;

    return aluguel;
}

Aluguel *aluguel_cria(Aluguel* aluguel, Carro* carro, char *data, int duracao)
{
    Aluguel *aluguel_auxiliar;
    aluguel_auxiliar->data_aluguel = (char *)malloc(11 * sizeof(char));
    aluguel_auxiliar->duracao = duracao;
    aluguel_auxiliar->status = 1;
    aluguel_auxiliar->carro = carro;
    carro_alugado(carro);

    // endereço do elemento imediatamente antes do novo elemento, na ordem alfabética:
    Aluguel *ref = aluguel_ordena(aluguel, data);
    if (ref == NULL)   /* verifica se o novo cadastro ficará na primeira posição da lista */
    {
        aluguel_auxiliar->prox_aluguel = aluguel;
        aluguel = aluguel_auxiliar;
    }
    else
    {
        aluguel_auxiliar->prox_aluguel = ref->prox_aluguel;
        ref->prox_aluguel = aluguel_auxiliar;
    }

    return aluguel;
}

void aluguel_libera(Aluguel *aluguel)
{
    Aluguel *A = aluguel;   /* ponteiro inicializado com a lista */
    Aluguel *t;             /* ponteiro auxiliar */

    // ==================================================
    // laço de repetição, enquanto valor de "P" não for [NULL] (Fim da lista):
    while (A != NULL) 
    {
        t = A->prox_aluguel;
        free(A->data_aluguel);
        carro_libera(A->carro);
        free(A);
        A = t;
    }
}

Aluguel *aluguel_ordena(Aluguel *aluguel, char *data_inicio)
{
    Aluguel *ref = NULL;            /* ponteiro para indicar endereço de referência, inicializado com [NULL] */
	Aluguel *aluguel_aux = aluguel;			/* cria um ponteiro auxiliar "aluguel_aux", inicializada com a lista "aluguel" */

    // O critério de parada será o fim da fila ou encontrar 
    // uma data que venha depois:
	while (aluguel_aux != NULL && compara_data(aluguel->data_aluguel, data_inicio) == -1)		/* verifica "P" chegou na posição */
	{
		ref = aluguel_aux;		                    /* "ref" aponta para o valor atual de "aluguel_aux" */
		aluguel_aux = aluguel_aux->prox_aluguel;	/* "aluguel_aux" passa a apontar para o próximo valor */
	}
	
	return ref; /* retorna o endereço de referência para o novo cadastro */
}