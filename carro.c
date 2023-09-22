#include <stdio.h>
#include "cliente.h"
#include "carro.h"

struct carro
{
    long int codigo; // acho que é o indentificador do carro
    int disponibilidade; // 1 seria desocupado e 0 ocupado
    char *modelo[20];
    Cliente *cliente;
    FILE *historico; // fazer um historico de quem ja alugou o carro, com as especificações 
};
