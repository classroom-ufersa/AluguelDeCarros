/* Dependência de módulo */
#include "../cliente/cliente.h"
#include "../carro/carro.h"

/* Funções Exportadas */

/*
Função que limpa o terminal de acordo com o SO do usuário
*/
char *clear(void);

// Função que exibe o menu principal
int menu_principal(void);

// Função que exibe o menu cliente
Cliente *menu_cliente(Cliente *cli);

// Função que exibe o menu carro
Carro *menu_carro(Carro *carro);

// Função que faz a comparação entre as strings
int compara(char *nome, char *nome_busca);

int teste_formato(char *num);

int teste_input(char *resp);

void delay(double segundos);