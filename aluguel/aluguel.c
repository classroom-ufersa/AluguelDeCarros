#include <stdio.h>
#include "aluguel.h"
#include "../carro/carro.h"

struct aluguel
{
    char *data_aluguel;
    char *duracao;
    Carro *carro;
};
