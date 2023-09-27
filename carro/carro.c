#include <stdio.h>
#include "cliente.h"
#include "carro.h"

struct carro
{
    long int codigo; // acho que é o identificador do carro
    int disponibilidade; // 1 seria desocupado e 0 ocupado
    char *modelo;
    Cliente *cliente;
    FILE *historico; // fazer um historico de quem ja alugou o carro, com as especificações 
};

Carro* carro_aluga()
{
    
}

void carro_lista()
{

}

void carro_disponivel()
{

}