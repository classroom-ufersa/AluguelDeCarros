#include <stdio.h>
#include <stdlib.h>
#include "aluguel.h"
#include "../carro/carro.h"
#include "../cliente/cliente.h"

struct aluguel
{
    char *data_aluguel;
    char *duracao;
    Carro *carro;
};

Aluguel *aluguel_cria(Aluguel* aluguel)
{
    Aluguel *novo_aluguel = (Aluguel*)malloc(sizeof(Aluguel));
    if (novo_aluguel == NULL)
    {
        printf("\nNao foi possivel concluir o aluguel\n");
        return aluguel;
    }

    novo_aluguel->data_aluguel = (char *)malloc(31 * sizeof(char));
    novo_aluguel->duracao = (char *)malloc(15 * sizeof(char));
    novo_aluguel->carro = (Carro *)malloc(sizeof(Carro));
}