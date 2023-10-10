#include <stdio.h>
#include <stdlib.h>
#include "../carro/carro.c"
#include "aluguel.h"
// #include "../cliente/cliente.h"

struct aluguel
{
    char *data_aluguel;
    int duracao;
    int status_aluguel;     /* 1 -> ativo, 0 -> finalizado */
    
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

    novo_aluguel->status_aluguel = 0;
    aluguel = novo_aluguel;

    return aluguel;
}

Aluguel *aluguel_cria(Aluguel* aluguel, Carro* carro, char *data, int duracao)
{
    // aloca o espaço necessário para o aluguel novo:
    Aluguel *novo_aluguel = (Aluguel*)malloc(sizeof(Aluguel));
    if (novo_aluguel == NULL)
    {
        printf("\nNao foi possivel criar o registro de aluguel\n");
        return NULL;
    }
    novo_aluguel->data_aluguel = (char *)malloc(11 * sizeof(char));

    // ==================================================
    // insere os dados do cliente:
    novo_aluguel->duracao = duracao;
    novo_aluguel->status_aluguel = 1;
    novo_aluguel->carro = carro;
    carro_alugado(carro);
    // printf(":).....");

    // ==================================================
    // encadea o endereço dos alugueis:

    // endereço do elemento imediatamente antes do novo elemento, na ordem cronológica:
    Aluguel *ref = aluguel_ordena(aluguel, data);
    if (ref == NULL)   /* verifica se o novo cadastro ficará na primeira posição da lista */
    {
        novo_aluguel->prox_aluguel = aluguel;
        aluguel = novo_aluguel;
    }
    else
    {
        novo_aluguel->prox_aluguel = ref->prox_aluguel;
        ref->prox_aluguel = novo_aluguel;
    }

    return aluguel;
}

void aluguel_libera(Aluguel *aluguel)
{
    Aluguel *aluguel_aux = aluguel;   /* ponteiro inicializado com a lista */
    Aluguel *aux;             /* ponteiro auxiliar */

    // ==================================================
    // laço de repetição, enquanto valor de "P" não for [NULL] (Fim da lista):
    while (aluguel_aux != NULL) 
    {
        aux = aluguel_aux->prox_aluguel;
        free(aluguel_aux->data_aluguel);
        // carro_libera(aluguel_aux->carro);
        free(aluguel_aux);
        aluguel_aux = aux;
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

char *aluguel_fim(Aluguel *aluguel)
{
    int data_inicio = data_para_num(aluguel->data_aluguel);
    char *data_fim = num_para_data(data_inicio + aluguel->duracao);
    return data_fim;
}
